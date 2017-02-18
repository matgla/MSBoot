#include "logger.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

#define TIME_BUFFER_SIZE 18

// Logger *Logger::pInstance = nullptr;
char buffer[TIME_BUFFER_SIZE];

Logger::Logger()
    : name_("default"),
      fd_(DEFAULT_FD)
{
}

Logger::Logger(const char* name, int fd)
    : name_(""),
      fd_(fd)
{
    std::memcpy(name_, name, strlen(name));
}

const char* Logger::getLevelString(const Level& level)
{
    switch (level)
    {
        case Level::DEBUG:
            return "DBG";
            break;
        case Level::ERROR:
            return "ERR";
            break;
        case Level::INFO:
            return "INF";
            break;
        case Level::TRACE:
            return "TRC";
            break;
        default:
            return "NON";
            break;
    }
}

// Logger::Logger()
// {
//     logLevel = Level::INFO;
//     logOutput = Output::STDOUT;
// }

const char* Logger::getTimeString()
{
    // auto t = std::time(nullptr);
    // struct tm *currentTime = std::localtime(&t);
    //std::strftime(buffer, TIME_BUFFER_SIZE, "%m/%d/%y %H:%M:%S", currentTime);
    return "00/00/00 00:00:00"; // TODO: Maybe it is possible to optimize size ?
}

// void logLine(Level level, const char *format, ...)
// {

// }

// void writeToFile(Level level, const char *format, ...)
// {

// }