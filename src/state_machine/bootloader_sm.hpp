#pragma once
#include <boost/sml.hpp>

#include "helpers.hpp"
#include "logger.hpp"

namespace sml = boost::sml;

class BootLoaderSm
{
    class Initial;
    class Initialized;


  public:
    // clang-format off
    BootLoaderSm() : logger_("bootloader_sm")
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
            //|--------STATE--------|-----------EVENT-----------|--GUARD---|-----------------ACTION------------------|--------TARGET--------|//
              *state<Initial>       + event<evInitialize>                  / call(this, &BootLoaderSm::initialize)   = state<Initialized>
        );
        // clang-format on
    }

    // actions
    void initialize()
    {
        logger_ << Level::INFO << "STM32 intialization ongoing\n";
        
    };

    Logger logger_;
};