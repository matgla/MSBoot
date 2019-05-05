#include <cstddef>

#include "modules/settings_module.hpp"

namespace msboot
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

std::size_t get_settings_size() const
{
    return eeprom_.read<uint32_t>(settings_size_address);
}

uint32_t SettingsModule::get_settings_crc() const
{
    return eeprom_.read<uin32_t>(settings_crc_address);
}

uint32_t SettingsModule::get_booting_flags() const
{
    return eeprom_.read<uint32_t>(booting_flags_address);
}

bool SettingsModule::is_booting_primary_firmware()
{
    return get_flag_value(get_booting_flags(), boot_primary_flag_position);
}

bool SettingsModule::is_booting_secondary_firmware()
{
    return get_flag_value(get_booting_flags(), boot_secondary_flag_position);
}


} // namespace settings
} // namespace msboot
