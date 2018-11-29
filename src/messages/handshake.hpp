#pragma once

#include <cstdint>
#include <optional>

#include <gsl/span>

namespace bootloader
{
namespace messages
{

struct Handshake
{
    constexpr static uint8_t id = 1;
    static std::optional<Handshake> deserialize(const gsl::span<const uint8_t>& payload)
    {
        if (payload.size() != 3)
        {
            return
        }

        return Handshake{
            .transation_id = };
    }

    uint8_t transation_id;
    uint8_t peer_minor_version;
    uint8_t peer_major_version;
};

} // namespace messages
} // namespace bootloader
