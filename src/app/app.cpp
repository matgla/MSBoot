#include "app/app.hpp"

#include "modules/booting/booting_module.hpp"
#include "modules/bootloader/bootloader_module.hpp"
#include "modules/settings/settings_module.hpp"

#include <msmp_usart/usart_host.hpp>
#include <msmp/broker/message_broker.hpp>
#include <hal/usart.hpp>

#include <msmp/serializer/serialized_message.hpp>
#include <msmp/serializer/message_deserializer.hpp>
#include <msmp/types.hpp>
#include <msmp/broker/typed_message_handler.hpp>

namespace msboot
{
namespace app
{

class TestMessage
{
public:
    constexpr static uint8_t id = 123;

    auto serialize() const
    {
        return msmp::serializer::SerializedUserMessage<>{}
            .compose_u8(id)
            .compose_string<20>(name)
            .build();
    }

    static TestMessage deserialize(const msmp::StreamType& payload)
    {
        TestMessage msg{};
        msmp::serializer::UserMessageDeserializer<> reader(payload);
        reader.drop_u8();
        msg.name = reader.decompose_string();
        return msg;
    }

    std::string name;
};

class TestMessageHandler : public msmp::broker::TypedMessageHandler<TestMessage>
{
public:
    TestMessageHandler(context::Context& context)
        : logger_(context.logger_factory().create("TestMessageHandler"))
    {

    }

    void handle(const TestMessage& msg) override
    {
        logger_.info() << "Received message: " << msg.name;
    }

private:
    eul::logger::logger logger_;
};

App::App()
    : context_(kernel_)
{
}

int App::run()
{
    modules::settings::SettingsModule settings_module(context_);
    kernel_.register_module(settings_module);

    modules::booting::BootingModule booting_module(context_);
    kernel_.register_module(booting_module);

    modules::bootloader::BootloaderModule bootloader_module(context_);
    kernel_.register_module(bootloader_module);

    bootloader_module.start();

    msmp::UsartHost host("HostA", hal::board::UsartContainer.get<hal::board::Usart0>());
    hal::board::UsartContainer.get<hal::board::Usart0>().init(9600);
    msmp::broker::MessageBroker broker(context_.logger_factory());

    TestMessageHandler handler(context_);
    broker.addHandler(handler);
    eul::logger::logger logger_(context_.logger_factory().create("Host"));
    host.onConnected([&logger_]{
        logger_.info() << "Peer connected!";
    });
    host.start();
    while (true)
    {
        sleep(1);
    }
    return 0;
}

} // namespace app
} // namespace msboot
