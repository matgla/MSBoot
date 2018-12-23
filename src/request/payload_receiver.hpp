#pragma once

#include <cstdint>
#include <type_traits>

#include <gsl/span>

#include <eul/function.hpp>
#include <eul/static_vector.hpp>

namespace request
{

constexpr std::size_t BUFFER_SIZE = 255;

struct PayloadReceiver
{
    using WriterCallback   = eul::function<void(const gsl::span<const uint8_t>&), sizeof(void*)>;
    using TransmitCallback = eul::function<void(const gsl::span<const uint8_t>&), sizeof(void*)>;
    PayloadReceiver::PayloadReceiver(const WriterCallback& writer, const TransmitCallback& transmitter);

    void receive(const uint8_t byte);

private:
    void receiveLength(const uint8_t byte);
    void receiveMessageType(const uint8_t byte);
    void receivePayload(const uint8_t byte);
    void receiveCrc(const uint8_t byte);
    void receiveControlCallback(const uint8_t byte);
    void verifyPayload();


    enum class States : uint8_t
    {
        Idle,
        ReceivingMessageType,
        ReceivingLength,
        ReceivingPayload,
        ReceivingCrc,
        ReceivingControlPayload,
        VerifyPayload
    };

    enum class MessageType : uint8_t
    {
        Control = 1,
        Data    = 2
    };

    WriterCallback writer_;
    TransmitCallback transmitter_;

    eul::static_vector<uint8_t, BUFFER_SIZE> buffer_;
    eul::static_vector<uint8_t, 4> crc_buffer_;

    uint8_t transaction_id_;
    uint8_t payload_length_;
    States state_;
    MessageType type_;
};

} // namespace request
