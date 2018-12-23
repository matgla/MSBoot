#pragma once

#include <cstdint>
#include <optional>

#include <string_view>

#include <gsl/span>

namespace request
{
namespace messages
{

struct Handshake
{
    constexpr static uint8_t id = 1;
    static std::optional<Handshake> deserialize(const gsl::span<const uint8_t>& payload);
    uint8_t transaction_id;
    uint8_t peer_major_version;
    uint8_t peer_minor_version;
};

} // namespace messages
} // namespace request
