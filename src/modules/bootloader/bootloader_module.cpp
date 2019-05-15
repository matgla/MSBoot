#include <cstdint>

#include <eul/kernel/kernel.hpp>

#include <CRC.h>

#include "modules/bootloader/bootloader_module.hpp"
#include "modules/settings/settings_module.hpp"
#include "context/context.hpp"

namespace msboot
{
namespace modules
{
namespace bootloader
{

BootloaderModule::BootloaderModule(context::Context& context)
    : module(this)
    , state_(States::Initializing)
    , kernel_(context.kernel())
    , logger_(context.logger_factory().create("BootloaderModule"))
    , client_connected_(false)
{

}

void BootloaderModule::start()
{
    if (state_ == States::Initializing)
    {
        logger_.info() << "Initializing bootloader";

        auto& settings = kernel_.get_module<settings::SettingsModule>()->get_settings();

        if (settings.is_flashing)
        {
            logger_.info() << "Bootloader mode: flashing";

            if (!client_connected_)
            {
                logger_.info() << "Waiting for connection to firmware provider";
            }

            state_ = States::Flashing;
            return;
        }

        if (settings.is_booting_primary)
        {
            logger_.info() << "Bootloader mode: booting primary partition";


        }
    }
}

void BootloaderModule::handle_event(const ClientConnected& client)
{
    logger_.info() << "Client connected";
    client_connected_ = true;
}

} // namespace bootloader
} // namespace modules
} // namespace msboot
