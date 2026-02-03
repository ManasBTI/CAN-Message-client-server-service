#pragma once

#include "CanServer.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <iostream>

 class CanClient
 {  private:
        void printMessage(const CanMessage& message) const;

        const CanServer& server_;
    public:
        explicit CanClient(const CanServer& server) ;

        void requestandPrint(uint32_t canId) const;

    
 };