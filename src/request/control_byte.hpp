#pragma once

#include <cstdint>

namespace request
{

enum class ControlByte : uint8_t
{
    StartFrame = 0x7e,
    EndFrame   = 0x55,
    EscapeCode = 0x7c
};

} // namespace request
