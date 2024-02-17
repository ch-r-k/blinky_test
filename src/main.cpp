//============================================================================
// APP example
//============================================================================
#include "qpcpp.hpp"   // QP/C++ real-time embedded framework
#include "blinky.hpp"  // DPP Application interface
#include "bsp.hpp"     // Board Support Package

//............................................................................
int main()
{
	QP::QF::init();			// initialize the framework
	BSP::init();			// initialize the BSP
	BSP::start();			// start the AOs/Threads
	return QP::QF::run();	// run the QF application
}
