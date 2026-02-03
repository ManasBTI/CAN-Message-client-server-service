# pragma once
#include <optional>
#include <array>
#include <cstdint>
#include <memory>
#include <unordered_map>

class CanMessage
{
public:

    CanMessage(uint32_t id,  uint8_t dlc, const std::array<uint8_t, 8>& payload);

    uint32_t getCanId() const;
    uint8_t getdlc() const; 
    const std::array<uint8_t, 8>& getpayload() const;
private:
    uint32_t canId_;
    uint8_t dlc_;
    std::array<uint8_t, 8> payload;
}; // namespace CAN_Task