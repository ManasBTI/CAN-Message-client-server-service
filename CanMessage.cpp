#include "CanMessage.h"
#include <stdexcept>


CanMessage::CanMessage(uint32_t id, uint8_t dlc, const std::array<uint8_t, 8>& payload)
    : canId_(id), dlc_(dlc), payload(payload)
{
    if (dlc > 8)
    {
        throw std::invalid_argument("DLC must be between 0 and 8");
    }
}

uint32_t CanMessage::getCanId() const
{
    return canId_;
}
uint8_t CanMessage::getdlc() const
{
    return dlc_;
}
const std::array<uint8_t, 8>& CanMessage::getpayload() const
{
    return payload;
}

