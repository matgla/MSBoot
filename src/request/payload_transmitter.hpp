#pragma once

#include <cstdint>

#include <gsl/span>

#include <eul/container/static_vector.hpp>
#include <eul/function.hpp>

namespace request
{

constexpr std::size_t max_payload_size = 255;

struct Message
{
    uint8_t transaction_id;
    uint8_t data_type;
    uint8_t length;
    uint8_t payload[max_payload_size];
};


template <uint8_t NumberOfFrames>
class PayloadTransmitter
{
public:
    using StreamType       = gsl::span<const uint8_t>;
    using TransmitCallback = eul::function<void(const StreamType&), sizeof(void*)>;

    PayloadTransmitter(const TransmitCallback& transmitter)
        : transaction_id_counter_(0), transmitter_(transmitter), state_(States::Idle)
    {
    }

    enum class TransmissionStatus : uint8_t
    {
        Accepted,
        TooBigPayload,
        BufferFull,
        DataBufferFull
    };

    TransmissionStatus send(const StreamType& payload)
    {
        if (payload.size() >= 255)
        {
            return TransmissionStatus::TooBigPayload;
        }

        if (message_buffer_.size() == message_buffer_.max_size())
        {
            return TransmissionStatus::BufferFull;
        }

        Message msg{
            .transaction_id = ++transaction_id_counter_,
            .data_type      = 0x02,
            .length         = payload.size()};

        std::copy(msg.payload, payload);

        message_buffer_.push_back(msg);

        return TransmissionStatus::Accepted;
    }

    void run()
    {
        switch (state_)
        {
            case States::TransmissionOngoing:
            {
            }
            break;
            case States::Transmitted:
            {
            }
            break;
        }
        while (message_buffer_.size())
        {
            transmitter_(message_buffer_.pop_back());
        }
    }

    void sendControl(const StreamType& payload)
    {
    }


protected:
    using MessageBuffer = eul::container::static_vector<Message, NumberOfFrames>;

    enum class States : uint8_t
    {
        TransmissionOngoing,
        Transmitted,
        Idle
    }

    uint8_t transaction_id_counter_;

    TransmitCallback transmitter_;
    States state_;
    MessageBuffer message_buffer_;
    DataBuffer data_buffer_;
};

} // namespace request