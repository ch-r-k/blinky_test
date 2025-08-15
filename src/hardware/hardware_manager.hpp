#pragma once

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
