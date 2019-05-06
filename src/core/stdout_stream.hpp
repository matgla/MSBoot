#pragma once

#include <iostream>

#include <eul/logger/logger_stream.hpp>

namespace msboot
{
namespace core
{

struct StdoutStream : public eul::logger::logger_stream
{
    void write(const std::string_view& data) override
    {
        std::cout << data;
    }
};

} // namespace core
} // namespace msboot
