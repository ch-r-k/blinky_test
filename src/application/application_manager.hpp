#ifndef APPLICATION_MANAGER_HPP
#define APPLICATION_MANAGER_HPP

#include "qpcpp.hpp"
#include "blinky/blinky.hpp"
#include "input_checker/input_checker.hpp"
#include "device/device_manager.hpp"

class ApplicationManager
{
   private:
    application_layer::Blinky ao_blinky;
    application_layer::InputChecker input_checker;

   public:
    ApplicationManager(DeviceManager& device_manager);
    ~ApplicationManager() = default;

    void start();
};

#endif  // APPLICATION_MANAGER_HPP
