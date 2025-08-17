#pragma once

#include "qpcpp.hpp"

enum AppSignals : QP::QSignal
{
    DUMMY_SIG = QP::Q_USER_SIG,
    MAX_PUB_SIG,  // the last published signal

    TIMEOUT_BLINKY_SIG,
    TIMEOUT_BUTTON_PRESS_SIG,
    BUTTON_PRESS_SIG,
    MAX_SIG  // the last signal
};