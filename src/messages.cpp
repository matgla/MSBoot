#include "messages.hpp"

Message::Message(u8 fd, u8 size)
    : fd_(fd),
      size_(size)
{
}

RequestDownload::RequestDownload()
    : Message(static_cast<u8>(FileDescriptors::SW_DWN),
          static_cast<u8>(Messages::SW_DWN_REQ))
{
}