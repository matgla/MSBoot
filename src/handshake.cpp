#include "handshake.hpp"
#include "deviceInfoReader.hpp"
#include "usart.hpp"

Handshake::Handshake()
    : connectedToClient_(false)
{
}

void Handshake::registerClient(const ClientInfo& clientInfo)
{
    connectedToClient_ = true;
    sendDeviceIdData();
}

void Handshake::sendDeviceIdData()
{
    DeviceInfo deviceInfo;
    deviceInfo.fd_ = static_cast<u8>(FileDescriptors::COMMUNICATION);
    deviceInfo.deviceSignature_ = deviceInfoReader::readDeviceSignature();
    deviceInfo.deviceRevision_ = deviceInfoReader::readDeviceRevision();
    deviceInfo.flashSize_ = deviceInfoReader::readFlashSize();
    deviceInfoReader::readUniqueId(deviceInfo.uniqueId_);

    hw::USART<hw::USARTS::USART1_PP1>::getUsart()
        .sendMessage(reinterpret_cast<u8*>(&deviceInfo), sizeof(DeviceInfo));
}