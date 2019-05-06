#include "app/app.hpp"

#include "modules/booting/booting_module.hpp"

namespace msboot
{
namespace app
{

App::App()
    : context_(kernel_)
{
}

int App::run()
{
    modules::booting::BootingModule booting_module(context_);
    kernel_.register_module(booting_module);

    kernel_.post_event(modules::booting::ClientConnected{});
    kernel_.post_event(modules::booting::BootPrimary{});
    kernel_.post_event(modules::booting::BootSecondary{});
    kernel_.post_event(modules::booting::FlashFirmware{});
    return 0;
}

} // namespace app
} // namespace msboot
