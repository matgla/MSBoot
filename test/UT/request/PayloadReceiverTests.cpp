#include <chrono>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gsl/span>

#include <hal/common/timer/timer_manager.hpp>
#include <hal/time/time.hpp>

#include <CRC.h>

#include "request/payload_receiver.hpp"

namespace request
{

using namespace std::chrono_literals;

constexpr auto transmission_timeout = 2s;

constexpr uint8_t start_frame             = 0x7e;
constexpr uint8_t nack                    = 0xff;
constexpr uint8_t nack_wrong_message_type = 0x01;

class PayloadReceiverShould : public ::testing::Test
{
};

TEST_F(PayloadReceiverShould, NackWhenWrongMessageTypeReceived)
{
    hal::time::Time time;
    hal::common::timer::TimerManager timer_manager;

    std::vector<uint8_t> transmitterBuffer;
    const auto transmitterCallback = [&transmitterBuffer](const gsl::span<const uint8_t>& data) {
        transmitterBuffer.insert(transmitterBuffer.end(), data.begin(), data.end());
    };

    const auto writerCallback = [](const gsl::span<const uint8_t>&) {};

    PayloadReceiver sut(writerCallback, transmitterCallback, time, timer_manager);

    EXPECT_THAT(transmitterBuffer, ::testing::SizeIs(0));
    sut.receive(start_frame);
    time += 1500ms;
    timer_manager.run();
    const uint8_t transaction_id = 1;
    sut.receive(transaction_id);
    constexpr uint8_t wrong_message_type = 0x99;
    sut.receive(wrong_message_type);
    ASSERT_THAT(transmitterBuffer, ::testing::SizeIs(2));
    EXPECT_THAT(transmitterBuffer, ::testing::ElementsAreArray({nack, nack_wrong_message_type}));
}

TEST_F(PayloadReceiverShould, ReceiveMessage)
{
    hal::time::Time time;
    hal::common::timer::TimerManager timer_manager;

    std::vector<uint8_t> transmitterBuffer;
    std::vector<uint8_t> messageBuffer;
    const auto transmitterCallback = [&transmitterBuffer](const gsl::span<const uint8_t>& data) {
        transmitterBuffer.insert(transmitterBuffer.end(), data.begin(), data.end());
    };

    const auto writerCallback = [&messageBuffer](const gsl::span<const uint8_t>& data) {
        messageBuffer.clear();
        messageBuffer.insert(messageBuffer.begin(), data.begin(), data.end());
    };

    PayloadReceiver sut(writerCallback, transmitterCallback, time, timer_manager);

    EXPECT_THAT(transmitterBuffer, ::testing::SizeIs(0));

    constexpr uint8_t transaction_id    = 1;
    constexpr uint8_t data_message_type = 2;
    constexpr uint8_t payload[]         = {'h', 'e', 'l', 'l', 'o', ' ', 't', 'h', 'e', 'r', 'e'};
    constexpr uint8_t payload_size      = sizeof(payload);

    sut.receive(start_frame);
    sut.receive(transaction_id);
    sut.receive(data_message_type);
    sut.receive(payload_size);

    for (auto byte : payload)
    {
        sut.receive(byte);
    }

    const uint32_t crc = CRC::Calculate(payload, sizeof(payload), CRC::CRC_32());
    const uint8_t crc0 = (crc & 0xFF000000) >> 24;
    const uint8_t crc1 = (crc & 0x00FF0000) >> 16;
    const uint8_t crc2 = (crc & 0x0000FF00) >> 8;
    const uint8_t crc3 = crc & 0x000000FF;

    sut.receive(crc0);
    sut.receive(crc1);
    sut.receive(crc2);
    sut.receive(crc3);
    ASSERT_THAT(messageBuffer, ::testing::SizeIs(payload_size));
    EXPECT_THAT(messageBuffer, ::testing::ElementsAreArray(payload));
}

} // namespace request
