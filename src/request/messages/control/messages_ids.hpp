#pragma once

#include <cstdint>

namespace request
{
namespace messages
{
namespace control
{

enum class ControlMessages : uint8_t
{
    Ack,
    Nack
};
}
} // namespace messages
} // namespace request