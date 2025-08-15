#ifndef USER_INDICATION_HPP
#define USER_INDICATION_HPP

#include "i_user_indication.hpp"
#include "hardware/output_pin/i_output_pin.hpp"

class UserIndication : public IUserIndication
{
   private:
    IOutputPin* outputPin = nullptr;

   public:
    UserIndication() = default;
    ~UserIndication() = default;
    void set() override;
    void reset() override;
    void setOutputPin(IOutputPin& init_output_pin);
};

#endif  // USER_INDICATION_HPP