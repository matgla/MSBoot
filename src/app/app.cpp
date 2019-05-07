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

    auto logger = context_.logger_factory().create("App");
    logger.info() << 1234 << ", " << 0x1234 << eul::logger::bin << ", 0x" << 0xabcd << ", 0x" << 0x00110100;
    logger.info() << eul::logger::boolalpha << "1: " << 1 << ", 2: " << 0 << ", 3: " << true << ", 4: " << false << ", 5: " << 2 << ", 6: " << eul::logger::hex << uint32_t(-1);
    return 0;
}

} // namespace app
} // namespace msboot
