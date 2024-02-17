//============================================================================
// Blinky example
//============================================================================

#ifndef BLINKY_HPP_
#define BLINKY_HPP_

namespace APP
{
enum AppSignals : QP::QSignal
{
	DUMMY_SIG = QP::Q_USER_SIG,
	MAX_PUB_SIG,  // the last published signal

	TIMEOUT_SIG,
	MAX_SIG  // the last signal
};

// opaque pointer to the Blinky AO
extern QP::QActive* const AO_Blinky;

}  // namespace APP

#endif	// BLINKY_HPP_
