#include "modules/booting/booting_module.hpp"

#include "context/context.hpp"

namespace msboot
{
namespace modules
{
namespace booting
{

BootingModule::BootingModule(const context::Context& context)
    : Module(this)
    , logger_(context.logger_factory().create("BootingModule"))
{
    logger_.info() << "Created";
}

void BootingModule::start()
{

}

void BootingModule::handle_event(const ClientConnected& event)
{
    logger_.info() << "Handle event: ClientConnected";
}

void BootingModule::handle_event(const FlashFirmware& event)
{
    logger_.info() << "Handle event: FlashFirmware";
}

void BootingModule::handle_event(const BootPrimary& event)
{
    logger_.info() << "Handle event: BootPrimary";
}

void BootingModule::handle_event(const BootSecondary& event)
{
    logger_.info() << "Handle event: BootSecondary";
}

} // namespace booting
} // namespace modules
} // namespace msboot
