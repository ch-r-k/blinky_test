#include "application_manager.hpp"
#include "qpcpp_signals.hpp"

ApplicationManager::ApplicationManager(DeviceManager& device_manager)
{
    ao_blinky.setUserIndication(device_manager.getUserIndication());
    input_checker.setUserInput(device_manager.getUserInput());
    input_checker.setReceiver(ao_blinky);
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
    ao_blinky.start(1U,                       // QP prio. of the AO
                    blinky_queue_sto,         // event queue storage
                    Q_DIM(blinky_queue_sto),  // queue length [events]
                    nullptr, 0U,              // no stack storage
                    nullptr);                 // no initialization param

    // instantiate and start AOs/threads...
    static QP::QEvt const* input_checker_queue_sto[10];
    input_checker.start(
        2U,                              // QP prio. of the AO
        input_checker_queue_sto,         // event queue storage
        Q_DIM(input_checker_queue_sto),  // queue length [events]
        nullptr, 0U,                     // no stack storage
        nullptr);                        // no initialization param
}