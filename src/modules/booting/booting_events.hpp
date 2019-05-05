#pragma once

#include <array>
#include <cstdint>

namespace msboot
{
namespace modules
{
namespace booting
{

class ClientConnected
{

};

struct FlashFirmware
{
    uint32_t size;
    uint32_t chunk_size;
};

struct ReceiveFirmwarePart
{
    uint16_t chunk_id;
    uint16_t chunk_size;
    std::array<uint8_t, 128> data;
};

struct FinishFirmwareFlashing
{
    uint32_t firmware_crc;
}

} // namespace booting
} // namespace modules
} // namespace msboot
