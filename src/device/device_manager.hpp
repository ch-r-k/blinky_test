#pragma once

#include "hardware/hardware_manager.hpp"
#include "user_indication/user_indication.hpp"

class DeviceManager
{
   private:
    UserIndication userIndication;

   public:
    DeviceManager(HardwareManager& hardware_manager);
    ~DeviceManager() = default;
    UserIndication& getUserIndication();
};
