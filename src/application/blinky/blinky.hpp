#pragma once

#include "device/user_indication/i_user_indication.hpp"
#include "qpcpp.hpp"

namespace application_layer
{
class Blinky : public QP::QActive
{
   private:
    QP::QTimeEvt m_timeEvt;
    IUserIndication* userIndication = nullptr;

   public:
    Blinky();
    ~Blinky() = default;

    void setUserIndication(IUserIndication& init_user_indication);

   protected:
    Q_STATE_DECL(initial);
    Q_STATE_DECL(idle);
    Q_STATE_DECL(off);
    Q_STATE_DECL(on);
};

}  // namespace application_layer