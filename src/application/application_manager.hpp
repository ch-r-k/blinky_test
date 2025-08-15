#ifndef APPLICATION_MANAGER_HPP
#define APPLICATION_MANAGER_HPP

#include "qpcpp.hpp"
#include "blinky/blinky.hpp"
#include "device/device_manager.hpp"

class ApplicationManager
{
   private:
    application_layer::Blinky aoBlinky;

   public:
    ApplicationManager(DeviceManager& device_manager);
    ~ApplicationManager() = default;

    void start();
};

#endif  // APPLICATION_MANAGER_HPP
