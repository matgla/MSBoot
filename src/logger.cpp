#include "logger.hpp"
#include <cstdio>
#include <cstdarg>
#include <ctime>

#define TIME_BUFFER_SIZE 18

Logger *Logger::pInstance = nullptr;
char buffer[TIME_BUFFER_SIZE];

const char* getLevelString(const Level &level) {
    switch(level) {
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

Logger::Logger() {
    logLevel = Level::INFO;
    logOutput = Output::STDOUT;
}

char *Logger::getTimeString() {
    auto t = std::time(nullptr);
    struct tm *currentTime = std::localtime(&t);
    std::strftime(buffer, TIME_BUFFER_SIZE, "%m/%d/%y %H:%M:%S", currentTime);
    return buffer;
}

void logLine(Level level, const char *format, ...) {}
void writeToFile(Level level, const char *format, ...) {

}