#pragma once

#include <cstdint>

#include <eul/kernel/fwd.hpp>

#include "context/fwd.hpp"

namespace msboot
{
namespace modules
{
namespace bootloader
{

class BootloaderModule
{
public:
    BootloaderModule(context::Context& context);

private:
    enum class States : uint8_t
    {
        Initializing,
        WaitingForClient,
        Flashing,
        Boot
    };

    States state_;
    eul::kernel::Kernel& kernel_;
};

} // namespace bootloader
} // namespace modules
} // namespace msboot
