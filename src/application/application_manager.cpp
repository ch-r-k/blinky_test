#include "application_manager.hpp"
#include "qpcpp_signals.hpp"

ApplicationManager::ApplicationManager(DeviceManager& device_manager)
{
    aoBlinky.setUserIndication(device_manager.getUserIndication());
}

void ApplicationManager::start()
{
    // initialize event pools
    static QF_MPOOL_EL(QP::QEvt) sml_pool_sto[20];
    QP::QF::poolInit(sml_pool_sto, sizeof(sml_pool_sto),
                     sizeof(sml_pool_sto[0]));

    // initialize publish-subscribe
    static QP::QSubscrList subscr_sto[MAX_PUB_SIG];
    QP::QActive::psInit(subscr_sto, Q_DIM(subscr_sto));

    // instantiate and start AOs/threads...
    static QP::QEvt const* blinky_queue_sto[10];
    aoBlinky.start(1U,                       // QP prio. of the AO
                   blinky_queue_sto,         // event queue storage
                   Q_DIM(blinky_queue_sto),  // queue length [events]
                   nullptr, 0U,              // no stack storage
                   nullptr);                 // no initialization param
}