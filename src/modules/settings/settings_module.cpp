#include <cstddef>

#include "modules/settings_module.hpp"

namespace msboot
{
namespace modules
{
namespace settings
{

constexpr std::size_t settings_size_address = 0x00;
constexpr std::size_t settings_crc_address = 0x01;

constexpr std::size_t booting_flags_address = 0x02;
constexpr std::size_t boot_primary_flag_position = 0x1;
constexpr std::size_t boot_secondary_flag_position = 0x2;
constexpr std::size_t flashing_flag_position = 0x03;

constexpr std::size_t primary_firmware_address = 0x03;
constexpr std::size_t primary_firmware_crc_address = 0x04;
constexpr std::size_t secondary_firmware_crc_address = 0x05;

constexpr std::size_t get_flag_value(const std::size_t flags, const std::size_t flag_offset)
{
    return (flags >> flag_offset) & 0x01;
}

SettingsModule::SettingsModule()
    : Module(this)
{

}

uint32_t SettingsModule::get_settings_crc() const
{
    return eeprom_.read_u32(settings_crc_address).value_or(0);
}

uint32_t SettingsModule::get_booting_flags() const
{
    return eeprom_.read_u8(booting_flags_address).value_or(0);
}

bool SettingsModule::is_booting_primary_firmware()
{
    return settings_.is_booting_primary;
}

bool SettingsModule::is_booting_secondary_firmware()
{
    return settings_.is_booting_secondary;
}

void SettingsModule::read_settings_from_eeprom()
{
    logger_.debug() << "Reading settings from eeprom";

    settings_.is_booting_primary = get_booting_flags() & 0x80;
    settings_.is_booting_secondary = get_booting_flags() & 0x40;
    settings_.is_flashing = get_booting_flags() & 0x20;
}

void SettingsModule::print_settings() const
{
    logger_.debug() << "Settings dump: {\n"
        << "is_booting_primary       : " << logger::manipulator::boolean << settings_.is_booting_primary << ",\n"
        << "is_booting_secondary     : " << settings_.is_booting_secondary << ",\n"
        << "is_flashing              : " << settings_.is_flashing << ",\n"
        << "primary_firmware_address : " << settings_.primary_firmware_address << ",\n"
        << "primary_firmware_size    : " << settings_.primary_firmware_size << ",\n"

}

} // namespace settings
} // namespace modules
} // namespace msboot
