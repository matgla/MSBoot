#pragma once

#include <cstdint>

#include <eul/kernel/event_listener.hpp>
#include <eul/kernel/module.hpp>

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
    , public eul::kernel::EventListener<ReceiveFirmwarePart>
    , public eul::kernel::EventListener<FinishFirmwareFlashing>
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

};

} // namespace booting
} // namespace modules
} // namespace msboot
