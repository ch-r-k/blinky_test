#ifndef HARDWARE_MANAGER_HPP
#define HARDWARE_MANAGER_HPP

#include "output_pin/i_output_pin.hpp"
#include "output_pin/output_pin.hpp"

class HardwareManager
{
   private:
    OutputPin ledPin;
    OutputPin TEST;

   public:
    HardwareManager();
    ~HardwareManager() = default;
    void run();
    IOutputPin& getLedPin();
};

#endif  // HARDWARE_MANAGER_HPP