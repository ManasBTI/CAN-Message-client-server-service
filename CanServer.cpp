#include "CanMessage.h"
#include "CanServer.h"
#include <unordered_map>

CanServer::CanServer()
{
    // Example initialization of the message database
    messageDatabase_[0x100] = {4, {0x11, 0x22, 0x33, 0x44, 0, 0, 0, 0}};
    messageDatabase_[0x200] = {2, {0xAA, 0xBB, 0, 0, 0, 0, 0, 0}};
};

std::optional<std::unique_ptr<CanMessage>> CanServer::requestMessage(uint32_t canId) const{
    auto it = messageDatabase_.find(canId);
    if (it == messageDatabase_.end())
    {
        return std::nullopt;
    }
    const Messagedata& data = it->second;
    return std::make_unique<CanMessage>(canId, data.dlc, data.payload);
};