#pragma once

#include <string_view>
#include <tuple>

#include <eul/container/observable/observing_node.hpp>
#include <eul/container/observable/observing_list.hpp>


namespace msboot
{
namespace core
{

class IModule
{
public:
    virtual ~IModule() = default;

    virtual void on_load() = 0;
    virtual void on_start() = 0;
    virtual void on_stop() = 0;

    virtual std::string_view get_name() const = 0;
};

class ObservedModule : public IModule
{
public:
    using ObservingNode = eul::container::observing_node<IModule*>;

    ObservedModule()
        : observing_node_(this)
    {
    }

    ObservingNode& observing_node()
    {
        return observing_node_;
    }

protected:
    ObservingNode observing_node_;

};

class ModuleBase : public ObservedModule
{
public:
    ModuleBase(std::string_view module_name)
        : module_name_(module_name)
    {
    }

    std::string_view get_name() const override
    {
        return module_name_;
    }

private:
    std::string_view module_name_;
};

template <typename... Services>
class Kernel
{
public:


    void start()
    {
        for (auto& module : modules_)
        {
            module.data()->on_start();
        }
    }

    template <typename ModuleType>
    auto& get_module()
    {
        return std::get<ModuleType>(modules_);
    }

    template <typename ModuleType>
    const auto& get_module() const
    {
        return std::get<ModuleType>(modules_);
    }
private:
    std::tuple<Services...> modules_;
};

} // namespace core
} // namespace msboot
