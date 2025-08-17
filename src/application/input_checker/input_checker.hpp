#pragma once

#include "device/user_input/i_user_input.hpp"
#include "qpcpp.hpp"

namespace application_layer
{
class InputChecker : public QP::QActive
{
   private:
    QP::QTimeEvt m_timeEvt;
    IUserInput* user_input = nullptr;
    QP::QActive* receiver = nullptr;

   public:
    InputChecker();
    ~InputChecker() = default;

    void setUserInput(IUserInput& init_user_input);
    void setReceiver(QP::QActive& init_ao);

   protected:
    Q_STATE_DECL(initial);
    Q_STATE_DECL(button_pressed);
    Q_STATE_DECL(button_released);
};

}  // namespace application_layer