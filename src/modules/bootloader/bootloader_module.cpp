#pragma once

#include <cstdint>

#include "modules/bootloader/bootloader_module.hpp"

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
};

} // namespace bootloader
} // namespace modules
} // namespace msboot
