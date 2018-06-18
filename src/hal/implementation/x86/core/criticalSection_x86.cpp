#include "hal/core/criticalSection.hpp"

#include <iostream>
#include <mutex>

namespace hal
{
namespace core
{

std::mutex globalLock;
std::mutex lockedMutex;
bool locked = false;
void startCriticalSection()
{
    std::lock_guard<std::mutex> lock(lockedMutex);
    globalLock.try_lock();
    locked = true;
}

void stopCriticalSection()
{
    std::lock_guard<std::mutex> lock(lockedMutex);

    if (locked)
    {
        locked = false;
        globalLock.unlock();
    }
}

} // namespace core
} // namespace hal
