#pragma once
#include <cstdio>
#include <cstdarg>


enum class Level {
    DEBUG,
    INFO,
    ERROR,
    TRACE
};

enum class Output {
    STDOUT,
    FILE,
    NONE
};

const char* getLevelString(const Level &level);

class Logger {
    public:
        static void init(Output primary, Output secondary) {};
        static void log(Level level, const char *nameSpace, const char *format, ...) {
            if(nullptr == pInstance) {
                static Logger logger;
                pInstance = &logger;
            }
            va_list args;

            if(pInstance->logOutput == Output::STDOUT) {
                printf("<%s> ", pInstance->getTimeString());
                printf("%s/%s: ", getLevelString(level), nameSpace);
                va_start (args, format);
                vprintf(format, args);
                printf("\n");
                va_end(args);
            } else if(pInstance->logOutput == Output::FILE) {
                
            }
        }
        static bool setOut(Output output, const char *fileName) {
            if(nullptr == pInstance) {
                static Logger logger;
                pInstance = &logger;
            }

            if(Output::FILE == output) {
                pInstance->logOutput = output;
                return true;
            }

            return false;
        }

        static bool setOut(Output output) {
            if(nullptr == pInstance) {
                static Logger logger;
                pInstance = &logger;
            }

            if(Output::FILE == output) {
                return false;
            } 

            pInstance->logOutput = output;
            return true;
        }
    private:
        Logger();
        static Logger *pInstance;
        Logger(Logger&) = delete;
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger(const Logger&&) = delete;
        
        void logLine(Level level, const char *format, ...);
        void writeToFile(Level level, const char *format, ...);
        void writeToStdOut(Level level, const char *format, ...);
        char *getTimeString();
        Level logLevel;
        Output logOutput;

};

#define LOG(x) Logger::log(x)