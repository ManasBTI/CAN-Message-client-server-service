#pragma once
#include "CanMessage.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_map>

class CanServer
{
public:
    CanServer();
    std::optional<std::unique_ptr<CanMessage>> requestMessage(uint32_t canId) const;
private:
    struct Messagedata {
        uint8_t dlc;
        std::array<uint8_t, 8> payload;
    };

    std::unordered_map<uint32_t, Messagedata> messageDatabase_;
};