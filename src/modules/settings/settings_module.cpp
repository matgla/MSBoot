#include <array>
#include <cstddef>
#include <optional>

#include <CRC.h>

#include "modules/settings/settings_module.hpp"
#include "context/context.hpp"

namespace msboot
{
namespace modules
{
namespace settings
{

constexpr std::size_t settings_crc_address              = 0x00;
constexpr std::size_t booting_flags_address             = 0x01;

constexpr std::size_t primary_firmware_address          = 0x02;
constexpr std::size_t primary_firmware_size_address     = 0x03;
constexpr std::size_t primary_firmware_crc_address      = 0x04;

constexpr std::size_t secondary_firmware_address        = 0x05;
constexpr std::size_t secondary_firmware_size_address   = 0x06;
constexpr std::size_t secondary_firmware_crc_address    = 0x07;

constexpr std::size_t get_flag_value(const std::size_t flags, const std::size_t flag_offset)
{
    return (flags >> flag_offset) & 0x01;
}

SettingsModule::SettingsModule(context::Context& context)
    : module(this)
    , logger_(context.logger_factory().create("SettingsModule"))
{
    read_settings_from_eeprom();
    print_settings();

    uint32_t calculated_crc = calculate_crc();
    if (calculated_crc != settings_.crc)
    {
        logger_.warning() << "Settings CRC verification failed. Settings CRC: 0x"
            << eul::logger::hex << settings_.crc << ", Calculated: 0x" << calculated_crc;
        logger_.warning() << "Initializing settings";
        settings_ = Settings();
        save_settings();
    }
}

uint32_t SettingsModule::get_booting_flags() const
{
    return eeprom_.read_u8(booting_flags_address).value_or(0);
}

void SettingsModule::read_settings_from_eeprom()
{
    logger_.debug() << "Reading settings from eeprom";

    settings_.is_booting_primary = get_booting_flags() & 0x80;
    settings_.is_booting_secondary = get_booting_flags() & 0x40;
    settings_.is_flashing = get_booting_flags() & 0x20;
    settings_.primary_firmware_address = eeprom_.read_u32(primary_firmware_address).value_or(0);
    settings_.primary_firmware_size = eeprom_.read_u32(primary_firmware_size_address).value_or(0);
    settings_.primary_firmware_crc = eeprom_.read_u32(primary_firmware_crc_address).value_or(0);
    settings_.secondary_firmware_address = eeprom_.read_u32(secondary_firmware_address).value_or(0);
    settings_.secondary_firmware_size = eeprom_.read_u32(secondary_firmware_size_address).value_or(0);
    settings_.secondary_firmware_crc = eeprom_.read_u32(secondary_firmware_crc_address).value_or(0);
    settings_.crc = eeprom_.read_u32(0x0).value_or(0);
}

void SettingsModule::print_settings() const
{
    logger_.debug() << "Settings dump: {\n"
        << "  is_booting_primary         : " << eul::logger::boolalpha << settings_.is_booting_primary << ",\n"
        << "  is_booting_secondary       : " << settings_.is_booting_secondary << ",\n"
        << "  is_flashing                : " << settings_.is_flashing << ",\n"
        << "  primary_firmware_address   : 0x" << eul::logger::hex << settings_.primary_firmware_address << ",\n"
        << "  primary_firmware_size      : 0x" << settings_.primary_firmware_size << ",\n"
        << "  primary_firmware_crc       : 0x" << settings_.primary_firmware_crc << ",\n"
        << "  secondary_firmware_address : 0x" << settings_.secondary_firmware_address << ",\n"
        << "  secondary_firmware_size    : 0x" << settings_.secondary_firmware_size << ",\n"
        << "  secondary_firmware_crc     : 0x" << settings_.secondary_firmware_crc << ",\n"
        << "  crc                        : 0x" << settings_.crc << "\n"
        << "}";

}

uint32_t SettingsModule::calculate_crc() const
{
    const std::array<uint32_t, 9> payload_for_crc {
        settings_.is_booting_primary,
        settings_.is_booting_secondary,
        settings_.is_flashing,
        settings_.primary_firmware_address,
        settings_.primary_firmware_size,
        settings_.primary_firmware_crc,
        settings_.secondary_firmware_address,
        settings_.secondary_firmware_size,
        settings_.secondary_firmware_crc,
    };
    return CRC::Calculate(payload_for_crc.data(), payload_for_crc.size(), CRC::CRC_32());
}

uint32_t SettingsModule::serialize_booting_flags() const
{
    uint32_t flags = 0;
    if (settings_.is_booting_primary)
    {
        flags |= 0x80;
    }
    else
    {
        flags &= 0x80;
    }

    if (settings_.is_booting_secondary)
    {
        flags |= 0x40;
    }
    else
    {
        flags &= 0x40;
    }

    if (settings_.is_flashing)
    {
        flags |= 0x20;
    }
    else
    {
        flags &= 0x20;
    }

    return flags;
}

void SettingsModule::save_settings()
{
    settings_.crc = calculate_crc();
    logger_.debug() << "Storing settings. CRC: 0x" << eul::logger::hex << settings_.crc;
    eeprom_.write_u8(booting_flags_address, serialize_booting_flags());
    eeprom_.write_u32(primary_firmware_address, settings_.primary_firmware_address);
    eeprom_.write_u32(primary_firmware_size_address, settings_.primary_firmware_size);
    eeprom_.write_u32(primary_firmware_crc_address, settings_.primary_firmware_crc);
    eeprom_.write_u32(secondary_firmware_address, settings_.secondary_firmware_address);
    eeprom_.write_u32(secondary_firmware_size_address, settings_.secondary_firmware_size);
    eeprom_.write_u32(secondary_firmware_crc_address, settings_.secondary_firmware_crc);
    eeprom_.write_u32(settings_crc_address, settings_.crc);
}

const Settings& SettingsModule::get_settings() const
{
    return settings_;
}

Settings& SettingsModule::get_settings()
{
    return settings_;
}

} // namespace settings
} // namespace modules
} // namespace msboot
