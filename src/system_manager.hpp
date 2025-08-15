#pragma once

#include "application/application_manager.hpp"
#include "device/device_manager.hpp"
#include "hardware/hardware_manager.hpp"

class SystemManager
{
   private:
    HardwareManager hardwareManager;
    DeviceManager deviceManager;
    ApplicationManager applicationManager;

   public:
    SystemManager();
    ~SystemManager();
    void run();
};