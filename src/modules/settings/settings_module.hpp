#pragma once

#include <cstdint>

#include <eul/kernel/module.hpp>
#include <eul/logger/logger.hpp>

#include <hal/memory/eeprom.hpp>

#include "context/fwd.hpp"

namespace msboot
{
namespace modules
{
namespace settings
{

struct Settings
{
    Settings()
        : is_booting_primary(0)
        , is_booting_secondary(0)
        , is_flashing(1)
        , primary_firmware_address(0)
        , primary_firmware_size(0)
        , primary_firmware_crc(0)
        , secondary_firmware_address(0)
        , secondary_firmware_size(0)
        , secondary_firmware_crc(0)
    {
    };

    bool is_booting_primary : 1;
    bool is_booting_secondary : 1;
    bool is_flashing : 1, :7;

    uint32_t primary_firmware_address;
    uint32_t primary_firmware_size;
    uint32_t primary_firmware_crc;
    uint32_t secondary_firmware_address;
    uint32_t secondary_firmware_size;
    uint32_t secondary_firmware_crc;
    uint32_t crc;
};

class SettingsModule
    : public eul::kernel::Module
{
public:
    SettingsModule(context::Context& context);

private:
    void read_settings_from_eeprom();
    uint32_t get_booting_flags() const;
    void print_settings() const;
    uint32_t calculate_crc() const;
    void save_settings();
    uint32_t serialize_booting_flags() const;

    Settings settings_;
    eul::logger::logger logger_;
    hal::memory::Eeprom eeprom_;
};

} // namespace settings
} // namespace modules
} // namespace msboot
