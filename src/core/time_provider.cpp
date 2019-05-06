#include <hal/time/time.hpp>

#include "core/time_provider.hpp"

namespace msboot
{
namespace core
{

std::chrono::milliseconds TimeProvider::milliseconds() const
{
    return hal::time::Time::milliseconds();
}

} // namespace core
} // namespace msboot
