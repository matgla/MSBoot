#pragma once

#include "logger.hpp"
#include <array>

template<std::size_t BUF_SIZE>
class Buffer
{
public:
    Buffer() : writerIndex_(0),
               readerIndex_(0)
    {

    }

    u16 write(char ch)
    {
        Logger logger;
        if (writerIndex_ >= BUF_SIZE - 1)
        {
            writerIndex_ = 0;
        }
        buffer_[writerIndex_] = ch;
        ++writerIndex_;
        buffer_[writerIndex_] = 0;
        return writerIndex_;
    }

    char getByte()
    {
        if (readerIndex_ >= BUF_SIZE -1)
        {
            readerIndex_ = 0;
        }
        return buffer_[readerIndex_++];
    }

    char* getData()
    {
        return buffer_;
    }

    u16 size()
    {
        return writerIndex_ - readerIndex_;
    }

private:
    void flush()
    {
        writerIndex_ = 0;
    }

    char buffer_[BUF_SIZE];
    u16 writerIndex_;
    u16 readerIndex_;
};