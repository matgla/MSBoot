#pragma once

#include <eul/logger/logger_factory.hpp>

#include "core/time_provider.hpp"
#include "core/stdout_stream.hpp"

namespace eul
{
namespace kernel
{
class Kernel;
} // namespace kernel
} // namespace eul

namespace msboot
{
namespace context
{

class Context
{
public:
    Context(eul::kernel::Kernel& kernel);

    const eul::logger::logger_factory& logger_factory() const;
private:
    core::StdoutStream stdout_stream_;
    core::TimeProvider time_;
    eul::logger::logger_factory logger_factory_;
    eul::kernel::Kernel& kernel_;
};

} // namespace context
} // namespace msboot
