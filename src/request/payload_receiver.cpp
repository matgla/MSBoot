#include "receiver/payload_receiver.hpp"


/*
TX
1) TransactionId
2) Length
3) MessageType
a - control, b - data
4a)


*/

namespace receiver
{

PayloadReceiver::PayloadReceiver(const WriterCallback& writer, const TransmitCallback& transmitter)
    : writer_(writer), transmitter_(transmitter), payload_length_(0), transaction_id_(0), state_(States::Idle)
{
}

void PayloadReceiver::receive(const uint8_t byte)
{
    switch (state_)
    {
        case States::Idle:
        {
            buffer_.flush();
            crc_buffer_.flush();

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
            }
            else if (type_ == MessageType::Data)
            {
                state_ = States::ReceivingPayload;
            }
            else
            {
                //report_wrong()
            }
        }
        break;
        case States::ReceivingPayload:
        {
            buffer_.push_back(byte);
            if (--payload_length_ = 0)
            {
                state_ = States::ReceivingCrc;
            }
        }
        break;
        case States::ReceivingCrc:
        {
            crc_buffer_.push_back(byte);
            if (crc_buffer_.size() == 4)
            {
            }
        }
        break;
    }
}

void receiveLength(const uint8_t byte);
void receiveMessageType(const uint8_t byte);
void receivePayload(const uint8_t byte);
void receiveCrc(const uint8_t byte);
void receiveControlCallback(const uint8_t byte);
void verifyPayload();


} // namespace receiver
