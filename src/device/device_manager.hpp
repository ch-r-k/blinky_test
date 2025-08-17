#pragma once

#include "hardware/hardware_manager.hpp"
#include "user_indication/user_indication.hpp"
#include "device/user_input/user_input.hpp"

class DeviceManager
{
   private:
    UserIndication user_indication;
    UserInput user_input;

   public:
    DeviceManager(HardwareManager& hardware_manager);
    ~DeviceManager() = default;
    UserIndication& getUserIndication();
    UserInput& getUserInput();
};
