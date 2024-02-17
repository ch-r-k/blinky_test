#include "qpcpp.hpp"   // QP/C++ real-time embedded framework
#include "blinky.hpp"  // Blinky Application interface
#include "bsp.hpp"     // Board Support Package

#include "stm32l4xx.h"	// CMSIS-compliant header file for the MCU used
#include "stm32l4xx_hal.h"

#ifdef Q_SPY
#error Simple Blinky Application does not provide Spy build configuration
#endif

//============================================================================
namespace
{  // unnamed namespace for local stuff with internal linkage

Q_DEFINE_THIS_FILE

// Q_DEFINE_THIS_FILE

}  // namespace

//============================================================================
// Error handler and ISRs...

extern "C"
{
	Q_NORETURN Q_onError(char const *const module, int_t const id)
	{
	// NOTE: this implementation of the assertion handler is intended only
	// for debugging and MUST be changed for deployment of the application
	// (assuming that you ship your production code with assertions
	// enabled).
	Q_UNUSED_PAR(module);
	Q_UNUSED_PAR(id);
	QS_ASSERTION(module, id, 10000U);

#ifndef NDEBUG
	// light up the user LED
	// for debugging, hang on in an endless loop...
	for (;;)
	{
	}
#endif

	NVIC_SystemReset();
	}
	//............................................................................
	void assert_failed(char const *const module, int_t const id);  // prototype
	void assert_failed(char const *const module, int_t const id)
	{
	Q_onError(module, id);
	}

	// ISRs used in the application
	// ==============================================
	void SysTick_Handler(void);	 // prototype
	void SysTick_Handler(void)
	{
	QP::QTimeEvt::TICK_X(0U, nullptr);  // process time events at rate 0

	QV_ARM_ERRATUM_838869();
	}

}  // extern "C"

//============================================================================
namespace BSP
{
void init()
{
	// Configure the MPU to prevent NULL-pointer dereferencing ...
	MPU->RBAR = 0x0U			       // base address (NULL)
		| MPU_RBAR_VALID_Msk	       // valid region
		| (MPU_RBAR_REGION_Msk & 7U);  // region #7
	MPU->RASR = (7U << MPU_RASR_SIZE_Pos)      // 2^(7+1) region
		| (0x0U << MPU_RASR_AP_Pos)    // no-access region
		| MPU_RASR_ENABLE_Msk;	       // region enable
	MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk	       // enable background region
		| MPU_CTRL_ENABLE_Msk;	       // enable the MPU
	__ISB();
	__DSB();

	// NOTE: SystemInit() has been already called from the startup code
	// but SystemCoreClock needs to be updated
	SystemCoreClockUpdate();

	// Hal init
	HAL_Init();

	// GPIO init
	GPIO_InitTypeDef gpioInitStruct = {NULL};

	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure GPIO pin Output Level
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

	// Configure GPIO pin : PB5
	gpioInitStruct.Pin = GPIO_PIN_5;
	gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioInitStruct.Pull = GPIO_NOPULL;
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);
}
//............................................................................
void start()
{
	// initialize event pools
	static QF_MPOOL_EL(QP::QEvt) smlPoolSto[20];
	QP::QF::poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

	// initialize publish-subscribe
	static QP::QSubscrList subscrSto[APP::MAX_PUB_SIG];
	QP::QActive::psInit(subscrSto, Q_DIM(subscrSto));

	// instantiate and start AOs/threads...

	static QP::QEvt const *blinkyQueueSto[10];
	APP::AO_Blinky->start(1U,			  // QP prio. of the AO
			  blinkyQueueSto,	  // event queue storage
			  Q_DIM(blinkyQueueSto),  // queue length [events]
			  nullptr, 0U,		  // no stack storage
			  nullptr);		  // no initialization param
}
//............................................................................
void ledOn()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}
//............................................................................
void ledOff()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
//............................................................................
void terminate(int16_t result) { Q_UNUSED_PAR(result); }

}  // namespace BSP

//============================================================================
namespace QP
{
// QF callbacks...
void QF::onStartup()
{
	// set up the SysTick timer to fire at BSP::TICKS_PER_SEC rate
	SysTick_Config(SystemCoreClock / BSP::TICKS_PER_SEC);

	// assign all priority bits for preemption-prio. and none to sub-prio.
	// NOTE: this might have been changed by STM32Cube.
	NVIC_SetPriorityGrouping(0U);

	// set priorities of ALL ISRs used in the system, see NOTE1
	NVIC_SetPriority(SysTick_IRQn, QF_AWARE_ISR_CMSIS_PRI + 1U);
	// ...

	// enable IRQs...
}
//............................................................................
void QF::onCleanup() {}
//............................................................................
void QV::onIdle()
{

#ifdef NDEBUG
	// Put the CPU and peripherals to the low-power mode.
	// you might need to customize the clock management for your application,
	// see the datasheet for your particular Cortex-M MCU.
	//
	// !!!CAUTION!!!
	// QV_CPU_SLEEP() contains the WFI instruction, which stops the CPU
	// clock, which unfortunately disables the JTAG port, so the ST-Link
	// debugger can no longer connect to the board. For that reason, the call
	// to QV_CPU_SLEEP() has to be used with CAUTION.
	//
	// NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
	// reset the board, then connect with ST-Link Utilities and erase the part.
	// The trick with BOOT(0) is it gets the part to run the System Loader
	// instead of your broken code. When done disconnect BOOT0, and start over.
	//
	// QV_CPU_SLEEP(); // atomically go to sleep and enable interrupts
	QF_INT_ENABLE();  // for now, just enable interrupts
#else
	QF_INT_ENABLE();  // just enable interrupts
#endif
}

}  // namespace QP