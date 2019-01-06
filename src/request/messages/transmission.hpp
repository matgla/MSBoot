#pragma once

#include <cstdint>

namespace request
{
namespace messages
{

struct Ack
{
    uint8_t transaction_id;
};

} // namespace messages
} // namespace request