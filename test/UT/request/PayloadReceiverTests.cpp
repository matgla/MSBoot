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

    // sut.receive();
    ASSERT_THAT(transmitterBuffer, ::testing::SizeIs(payload_size));
    EXPECT_THAT(transmitterBuffer.front(), nack);
}

} // namespace request
