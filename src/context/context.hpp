#pragma once

#include <eul/logger/logger_factory.hpp>
#include <eul/kernel/fwd.hpp>

#include "core/time_provider.hpp"
#include "core/stdout_stream.hpp"

namespace msboot
{
namespace context
{

class Context
{
public:
    Context(eul::kernel::kernel& kernel);

    const eul::logger::logger_factory& logger_factory() const;
    eul::kernel::kernel& kernel();

private:
    core::StdoutStream stdout_stream_;
    core::TimeProvider time_;
    eul::logger::logger_factory logger_factory_;
    eul::kernel::kernel& kernel_;
};

} // namespace context
} // namespace msboot
