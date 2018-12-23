#include "app/app.hpp"

#include <hal/common/timer/timeout_timer.hpp>
#include <hal/common/timer/timer_manager.hpp>
#include <hal/time/time.hpp>

int main()
{
    hal::common::timer::TimerManager timer_manager;
    hal::time::Time time_provider;
    hal::common::timer::TimeoutTimer timeout_timer(time_provider);
    timer_manager.register_timer(timeout_timer);
    app::App app;
    return app.run();
}
