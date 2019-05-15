#pragma once

#include <cstdint>

#include <eul/kernel/fwd.hpp>
#include <eul/kernel/event_listener.hpp>
#include <eul/logger/logger.hpp>

#include "modules/bootloader/bootloader_events.hpp"
#include "context/fwd.hpp"

namespace msboot
{
namespace modules
{
namespace bootloader
{

class BootloaderModule
    : public eul::kernel::module
    , public eul::kernel::event_listener<ClientConnected>
{
public:
    BootloaderModule(context::Context& context);
    void start();

private:
    enum class States : uint8_t
    {
        Initializing,
        WaitingForClient,
        Flashing,
        Boot
    };

    void handle_event(const ClientConnected& client) override;

    States state_;
    eul::kernel::kernel& kernel_;
    eul::logger::logger logger_;
    bool client_connected_;
};

} // namespace bootloader
} // namespace modules
} // namespace msboot
