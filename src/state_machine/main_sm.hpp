#pragma once
#include <boost/sml.hpp>

#include "logger.hpp"


//<-
namespace
{
template <class R, class... Ts>
auto call_impl(R (*f)(Ts...))
{
    return [f](Ts... args) { return f(args...); };
}
template <class T, class R, class... Ts>
auto call_impl(T* self, R (T::*f)(Ts...))
{
    return [self, f](Ts... args) { return (self->*f)(args...); };
}
template <class T, class R, class... Ts>
auto call_impl(const T* self, R (T::*f)(Ts...) const)
{
    return [self, f](Ts... args) { return (self->*f)(args...); };
}
template <class T, class R, class... Ts>
auto call_impl(const T* self, R (T::*f)(Ts...))
{
    return [self, f](Ts... args) { return (self->*f)(args...); };
}
/**
 * Simple wrapper to call free/member functions
 * @param args function, [optional] this
 * @return function(args...)
 */
auto call = [](auto... args) { return call_impl(args...); };
}
//->

//using usart = hw::USART<hw::USARTS::USART1_PP1>::getUsart();
namespace sml = boost::sml;

class MainSm
{
    class Initial;
    class Initialized;


  public:
    // clang-format off
    MainSm() : logger_("main_sm")
    {

    }

    // clang-format on

    struct evInitialize
    {
    };


    auto operator()() noexcept
    {
        using namespace sml;
        // clang-format off
        return make_transition_table(
            //|--------STATE--------|------------EVENT---------------|--GUARD---|------------ACTION-------------|--------TARGET--------|//
              *state<Initial>       + event<evInitialize>                       / call(this, &MainSm::initialize)                   = state<Initialized>
        );


        // clang-format on
    }

    void initialize()
    {
        logger_ << Level::INFO << "STM32 is under initialization\n";
    };

    Logger logger_;
};