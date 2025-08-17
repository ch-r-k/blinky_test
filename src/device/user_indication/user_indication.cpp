#include "user_indication.hpp"
#include "hardware/driver/output_pin/i_gpio_pin.hpp"

void UserIndication::set() { outputPin->set(); }

void UserIndication::reset() { outputPin->reset(); }

void UserIndication::setOutputPin(IGpioPin& init_output_pin)
{
    this->outputPin = &init_output_pin;
}