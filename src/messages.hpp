#pragma once

#include "types.h"

enum class FileDescriptors
{
    LOG = 1,
    SW_DWN = 10
};

enum class Messages
{
    SW_DWN_REQ = 10
};

struct Message
{
    Message(u8 fd = 0, u8 size = 0);
    ~Message() = default;

    u8 fd_;
    u8 size_;
    u8 payload_[255];
};

struct RequestDownload : public Message
{
    RequestDownload();
};