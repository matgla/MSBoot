#pragma once

#include <cstdint>

#include <eul/kernel/module.hpp>
#include <eul/logger/logger.hpp>

#include <hal/memory/eeprom.hpp>

namespace msboot
{
namespace settings
{

class SettingsModule
    : public eul::kernel::Module
{
public:
    SettingsModule();

    void initialize();

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
    uint32_t get_secondary_firmware_address() const;


private:

    uint32_t get_booting_flags() const;

    eul::logger::Logger
    hal::memory::Eeprom eeprom_;
};

} // namespace settings
} // namespace msboot
