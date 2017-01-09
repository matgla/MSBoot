#pragma once

#include <array>

#include "types.h"

template<std::size_t BUF_SIZE>
class Buffer
{
public:
    Buffer() : writerIndex_(0),
               readerIndex_(0),
               size_(0)
    {

    }

    u16 write(u8 ch)
    {
        if (writerIndex_ >= BUF_SIZE )
        {
            writerIndex_ = 0;
        }
        incrementSize();
        buffer_[writerIndex_++] = ch;
        return writerIndex_;
    }

    u8 getByte()
    {
        if (size_)
        {
            if (readerIndex_ >= BUF_SIZE)
            {
                readerIndex_ = 0;
            }
            size_--;
            return buffer_[readerIndex_++];
        }
        return 0;
    }

    u8* getData()
    {
        return buffer_;
    }

    u16 size()
    {
        return size_;
    }

private:
    void flush()
    {
        writerIndex_ = 0;
    }

    void incrementSize()
    {
        if (size_ < BUF_SIZE)
        {
            ++size_;
        }
        else
        {
            ++readerIndex_;
        }
    }
    u8 buffer_[BUF_SIZE];
    u16 writerIndex_;
    u16 readerIndex_;
    u16 size_;
};