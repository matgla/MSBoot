#pragma once

#include <chrono>

#include <eul/time/i_time_provider.hpp>

namespace msboot
{
namespace core
{

class TimeProvider : public eul::time::i_time_provider
{
public:
    std::chrono::milliseconds milliseconds() const override;
};

} // namespace core
} // namespace msboot
