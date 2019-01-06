#include "request/payload_receiver.hpp"

#include <chrono>
#include <iostream>

#include <CRC.h>

/*
TX
1) TransactionId
2) Length
3) MessageType
a - control, b - data
4a)
*/

namespace request
{

using namespace std::chrono_literals;

constexpr auto TransmissionTimeout = 2s;

PayloadReceiver::PayloadReceiver(const WriterCallback& writer, const TransmitCallback& transmitter, hal::time::Time& time, hal::common::timer::TimerManager& timer_manager)
    : writer_(writer), transmitter_(transmitter), payload_length_(0), transaction_id_(0), state_(States::Idle), receiving_special_character_(false), timer_(time)
{
    timer_.setCallback([this]() {
        state_ = States::Idle;
        // respondNack();
    });

    timer_manager.register_timer(timer_);
}

void PayloadReceiver::receive(const uint8_t byte)
{
    if (!receiving_special_character_)
    {
        if (receiveControl(static_cast<ControlByte>(byte)) == ProcessingState::Completed)
        {
            return;
        }
    }
    else
    {
        receiving_special_character_ = false;
    }

    processState(byte);
}

PayloadReceiver::ProcessingState PayloadReceiver::receiveControl(const ControlByte byte)
{
    if (byte == ControlByte::StartFrame)
    {
        state_ = States::StartTransmission;
        return ProcessingState::NotCompleted;
    }
    else if (byte == ControlByte::EscapeCode)
    {
        receiving_special_character_ = true;
        return ProcessingState::Completed;
    }
    else if (byte == ControlByte::EndFrame)
    {
        state_ = States::TransmissionEnd;
        return ProcessingState::NotCompleted;
    }
    return ProcessingState::NotCompleted;
}

void receiveLength(const uint8_t byte);
void receiveMessageType(const uint8_t byte);
void receivePayload(const uint8_t byte);
void receiveCrc(const uint8_t byte);
void receiveControlCallback(const uint8_t byte);

void PayloadReceiver::processPayload()
{
    if (verifyPayload())
    {
        StreamType span(buffer_.data(), static_cast<StreamType::index_type>(buffer_.size()));
        writer_(span);
        respondAck();
    }
    else
    {
        respondNack(messages::control::Nack::Reason::CrcMismatch);
    }
}


bool PayloadReceiver::verifyPayload()
{
    const uint32_t payload_crc = CRC::Calculate(buffer_.data(), buffer_.size(), CRC::CRC_32());

    uint32_t received_crc = static_cast<uint32_t>(crc_buffer_[0]) << 24;
    received_crc |= static_cast<uint32_t>(crc_buffer_[1]) << 16;
    received_crc |= static_cast<uint32_t>(crc_buffer_[2]) << 8;
    received_crc |= static_cast<uint32_t>(crc_buffer_[3]);
    return payload_crc == received_crc;
}

void PayloadReceiver::respondNack(const messages::control::Nack::Reason reason) const
{
    const uint8_t nack[] = {
        static_cast<const uint8_t>(ControlByte::StartFrame),
        // static_cast<const uint8_t>(ControlMessage::Nack),
        static_cast<const uint8_t>(reason),
        transaction_id_};
    transmitter_(nack);
}

void PayloadReceiver::respondAck() const
{
    const uint8_t ack[] = {
        static_cast<const uint8_t>(ControlByte::StartFrame),
        // static_cast<const uint8_t>(ControlMessage::Ack),
        transaction_id_};
    transmitter_(ack);
}

void PayloadReceiver::processState(const uint8_t byte)
{
    switch (state_)
    {
        case States::StartTransmission:
        {
            buffer_.flush();
            crc_buffer_.flush();

            state_ = States::ReceivingTransactionId;
        }
        break;
        case States::ReceivingTransactionId:
        {
            transaction_id_ = byte;
            state_          = States::ReceivingMessageType;
        }
        break;
        case States::ReceivingMessageType:
        {
            type_ = static_cast<MessageType>(byte);
            if (type_ == MessageType::Control)
            {
                state_ = States::ReceivingControlPayload;
                return;
            }
            if (type_ == MessageType::Data)
            {
                state_ = States::ReceivingLength;
                return;
            }
            else
            {
                respondNack(messages::control::Nack::Reason::WrongMessageType);
                state_ = States::Idle;
            }
        }
        break;
        case States::ReceivingLength:
        {
            payload_length_ = byte;
            state_          = States::ReceivingPayload;
        }
        break;
        case States::ReceivingPayload:
        {
            buffer_.push_back(byte);

            if (--payload_length_ == 0)
            {
                state_          = States::ReceivingCrc;
                payload_length_ = 4;
            }
        }
        break;
        case States::ReceivingCrc:
        {
            crc_buffer_.push_back(byte);
            if (--payload_length_ == 0)
            {
                processPayload();
                state_ = States::TransmissionEnd;
                return;
            }
        }
    }
}

} // namespace request
