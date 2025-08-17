#pragma once

#include "driver/output_pin/gpio_pin.hpp"
#include "hardware/driver/output_pin/i_gpio_pin.hpp"

class HardwareManager
{
   private:
    GpioPin led_pin{GpioPin::Port::PORT_A, GpioPin::Pin::PIN_5,
                    GpioPin::Mode::PUSH_PULL, GpioPin::Pull::NOPULL,
                    GpioPin::Speed::LOW};

    GpioPin button_pin{GpioPin::Port::PORT_C, GpioPin::Pin::PIN_13,
                       GpioPin::Mode::INPUT, GpioPin::Pull::PULL_UP,
                       GpioPin::Speed::LOW};

   public:
    HardwareManager();
    ~HardwareManager() = default;
    void run();
    IGpioPin& getLedPin();
    IGpioPin& getButtonPin();
};
