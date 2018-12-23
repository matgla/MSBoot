#include <chrono>

#include <gtest/gtest.h>

#include "request/payload_receiver.hpp"

namespace request
{

using namespace std::chrono_literals;

constexpr auto transmission_timeout = 2s;

class PayloadReceiverShould : public ::testing::Test
{
};

TEST_F(PayloadReceiverShould, NackWhenWrongMessageTypeReceived)
{
    PayloadReceiver sut;
    const uint8_t wrongMessageType = 90;
    sut.receive(wrongMessageType);
}

} // namespace request
