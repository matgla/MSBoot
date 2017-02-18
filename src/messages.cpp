#include "messages.hpp"

MessageHeader::MessageHeader(u8 fd)
    : fd_(fd)
{
}

RequestDownload::RequestDownload()
{
    id_ = static_cast<u8>(Messages::SW_DWN_REQ);
}

ClientInfo::ClientInfo()
{
    id_ = static_cast<u8>(Messages::CLIENT_INFO);
}