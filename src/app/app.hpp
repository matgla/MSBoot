#pragma once

#include "context/context.hpp"

#include <eul/kernel/kernel.hpp>

namespace msboot
{
namespace app
{

class App
{
public:
    App();
    int run();

private:
    eul::kernel::Kernel kernel_;
    context::Context context_;
};

} // namespace app
} // namespace msboot