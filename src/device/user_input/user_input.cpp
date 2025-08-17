#include "user_input.hpp"
#include "hardware/driver/output_pin/i_gpio_pin.hpp"

bool UserInput::get() { return !input_pin->get(); }

void UserInput::setInputPin(IGpioPin& init_output_pin)
{
    input_pin = &init_output_pin;
}