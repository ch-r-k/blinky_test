//============================================================================
// QP/C++ Real-Time Embedded Framework
//============================================================================
//! @date Last updated on: 2022-08-25
//! @version Last updated Zephyr 3.1.99 and @ref qpcpp_7_1_0
//!
//! @file
//! @brief Blinky example
//!

#include "qpcpp.hpp"
#include "input_checker.hpp"
#include "qpcpp_signals.hpp"

namespace application_layer
{
//............................................................................
InputChecker::InputChecker()
    : QP::QActive(&initial), m_timeEvt(this, TIMEOUT_BUTTON_PRESS_SIG, 0U)
{
    // empty
}

// HSM definition ------------------------------------------------------------
Q_STATE_DEF(InputChecker, initial)
{
    (void)e;  // unused parameter

    // arm the time event to expire in half a second and every half second
    m_timeEvt.armX(1000, 200);
    return tran(&button_released);
}
//............................................................................
Q_STATE_DEF(InputChecker, button_released)
{
    QP::QState status;
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
        {
            status = Q_RET_HANDLED;
            break;
        }
        case TIMEOUT_BUTTON_PRESS_SIG:
        {
            if (user_input->get())
            {
                static QP::QEvt const my_evt{BUTTON_PRESS_SIG};
                receiver->POST(&my_evt, this);

                return tran(&button_pressed);
            }
            else
            {
                status = Q_RET_HANDLED;
            }
            break;
        }
        default:
        {
            status = super(&top);
            break;
        }
    }
    return status;
}

//............................................................................
Q_STATE_DEF(InputChecker, button_pressed)
{
    QP::QState status;
    switch (e->sig)
    {
        case Q_ENTRY_SIG:
        {
            status = Q_RET_HANDLED;
            break;
        }
        case TIMEOUT_BUTTON_PRESS_SIG:
        {
            if (!user_input->get())
            {
                return tran(&button_released);
            }
            else
            {
                status = Q_RET_HANDLED;
            }
            status = Q_RET_HANDLED;
            break;
        }
        default:
        {
            status = super(&top);
            break;
        }
    }
    return status;
}

//............................................................................
void InputChecker::setUserInput(IUserInput& init_user_input)
{
    user_input = &init_user_input;
}

void InputChecker::setReceiver(QP::QActive& init_ao) { receiver = &init_ao; }

}  // namespace application_layer
