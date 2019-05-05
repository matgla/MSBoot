#pragma once

#include <cstdint>

#include <eul/kernel/event_listener.hpp>
#include <eul/kernel/module.hpp>

#include <eul/logger/logger.hpp>

#include "modules/booting/booting_events.hpp"

namespace msboot
{
namespace modules
{
namespace booting
{
/* Module flashes secondary partition if mcu has enough space for two partitions */

class BootingModule
    : public eul::kernel::Module
    , public eul::kernel::EventListener<ClientConnected>
    , public eul::kernel::EventListener<FlashFirmware>
    , public eul::kernel::EventListener<BootPrimary>
    , public eul::kernel::EventListener<BootSecondary>
{
public:
    void start();

private:
    enum class State : uint8_t
    {
        NotInitialized,
        Initialized,
        CheckingBootingOptions,
        WaitingForExternalConnection,
        Flashing,
        BootPrimaryPartition,
        BootSecondaryPartition,
    };

    void initialize();
    void waiting_for_external_connection();
    void waiting_for_external_connection_for_flashing();
    void flash();
    void boot_primary();
    void boot_secondary();

    static auto& create_logger();

    eul::logger::logger& logger_;
};

} // namespace booting
} // namespace modules
} // namespace msboot
