#pragma once

#include <cstdint>

#include <eul/kernel/module.hpp>
#include <eul/logger/logger.hpp>

#include <hal/memory/eeprom.hpp>

namespace msboot
{
namespace modules
{
namespace settings
{

struct Settings
{
    bool is_booting_primary : 1;
    bool is_booting_secondary : 1;
    bool is_flashing : 1, :7;

    uint32_t primary_firmware_address;
    uint32_t primary_firmware_size;
    uint32_t secondary_firmware_address;
    uint32_t secondary_firmware_size;
    uint32_t crc;
};

class SettingsModule
    : public eul::kernel::Module
{
public:
    SettingsModule();

    std::size_t get_settings_size() const;
    uint32_t get_settings_crc() const;
    uint32_t set_settings_crc(uint32_t crc);

    bool is_booting_primary_firmware() const;
    bool is_booting_secondary_firmware() const;
    bool is_flashing_flag_set() const;
    void set_booting_flag();

    uint32_t get_primary_firmware_address() const;
    uint32_t get_primary_firmware_size() const;
    uint32_t get_secondary_firmware_address() const;
    uint32_t get_secondary_firmware_size() const;


private:
    void read_settings_from_eeprom();
    uint32_t get_booting_flags() const;
    void print_settings() const;

    Settings settings_;
    eul::logger::logger logger_;
    hal::memory::Eeprom eeprom_;
};

} // namespace settings
} // namespace modules
} // namespace msboot
