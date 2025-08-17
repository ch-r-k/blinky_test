#pragma once

#include "i_user_indication.hpp"
#include "hardware/driver/output_pin/i_gpio_pin.hpp"

class UserIndication : public IUserIndication
{
   private:
    IGpioPin* outputPin = nullptr;

   public:
    UserIndication() = default;
    ~UserIndication() = default;
    void set() override;
    void reset() override;
    void setOutputPin(IGpioPin& init_output_pin);
};
