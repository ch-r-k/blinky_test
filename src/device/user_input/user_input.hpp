#pragma once

#include "i_user_input.hpp"
#include "hardware/driver/output_pin/i_gpio_pin.hpp"

class UserInput : public IUserInput
{
   private:
    IGpioPin* input_pin = nullptr;

   public:
    UserInput() = default;
    ~UserInput() = default;
    bool get() override;

    void setInputPin(IGpioPin& init_input_pin);
};
