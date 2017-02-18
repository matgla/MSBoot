#pragma once

#include "types.h"

enum class FileDescriptors
{
    LOG = 1,
    SW_DWN = 10,
    COMMUNICATION = 11
};

enum class Messages
{
    ACK = 0x06,
    SW_DWN_REQ = 0x0a,
    CLIENT_INFO = 0x0b
};

struct MessageHeader
{
    MessageHeader(u8 fd = 0);
    ~MessageHeader() = default;

    u8 fd_;
    u8 id_;
};

struct RequestDownload : public MessageHeader
{
    using MessageHeader::MessageHeader;
    RequestDownload();
    ~RequestDownload() = default;
};

struct ClientInfo : public MessageHeader
{
    using MessageHeader::MessageHeader;
    ClientInfo();
    ~ClientInfo() = default;
    char name_[10];
};