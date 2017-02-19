#pragma once

#include "buffer.hpp"
#include "types.h"

template <std::size_t BUF_SIZE>
class ReaderWriterBuffer
{
  public:
    u32 size()
    {
        return readerBuf_.size() + writerBuf_.size();
    }

    u8 getByte()
    {
        synchronizeBuffer();
        return readerBuf_.getByte();
    }

    template <typename Type>
    u16 write(Type byte)
    {
        return writerBuf_.write(byte);
    }

    template <typename Type>
    void write(Type* str)
    {
        writerBuf_.write(str);
    }

    template <typename Type>
    void write(Type* payload, u8 size)
    {
        for (u16 i = 0; i < size; ++i)
        {
            writerBuf_.write(payload[i]);
        }
    }

    u16 findInBuffer(u8 value)
    {
        synchronizeBuffer();
        for (int i = 0; i < readerBuf_.size(); ++i)
        {
            if (readerBuf_.getValue(i) == value)
            {
                return i;
            }
        }

        return -1;
    }

    void removeAt(u16 pos)
    {
        readerBuf_.removeFromBuffer(pos);
    }

    void flush()
    {
        readerBuf_.flush();
        writerBuf_.flush();
    }

  private:
    void synchronizeBuffer()
    {
        while (writerBuf_.size())
        {
            readerBuf_.write(writerBuf_.getByte());
        }
    }

    Buffer<BUF_SIZE> readerBuf_;
    Buffer<BUF_SIZE> writerBuf_;
};