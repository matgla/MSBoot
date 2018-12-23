#include "request/messages/handshake.hpp"

namespace request
{
namespace messages
{

std::optional<Handshake> Handshake::deserialize(const gsl::span<const uint8_t>& payload)
{
    if (payload.size() != 3)
    {
        return std::optional<Handshake>();
    }

    return Handshake{
        .transaction_id     = payload[0],
        .peer_major_version = payload[1],
        .peer_minor_version = payload[2]};
}

} // namespace messages
} // namespace request
