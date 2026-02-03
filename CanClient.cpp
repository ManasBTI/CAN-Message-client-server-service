#include "CanClient.h"
#include <iostream>
#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
using namespace std;


CanClient::CanClient(const CanServer &server) : server_(server) {
}

void CanClient::requestandPrint(uint32_t canId) const {
    auto response = server_.requestMessage(canId);
    if (!response.has_value()){
        cout << "CAN ID 0x" << hex << canId<< "not supported\n\n";
        return;
    }
    const unique_ptr<CanMessage>& message = response.value();
    printMessage(*message);
}

void CanClient::printMessage(const CanMessage& message) const {
    
    cout << "CAN ID: 0x" << hex << message.getCanId() << "\n";
    cout << "DLC: " << dec << static_cast<int>(message.getdlc()) << "\n";
    cout << "Payload: ";
    for (uint8_t i = 0; i < message.getdlc(); ++i) {
        cout << "0x" << hex << static_cast<int>(message.getpayload()[i]) << " ";
    }
    cout << "\n\n";
}