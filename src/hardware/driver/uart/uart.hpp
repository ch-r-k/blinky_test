#pragma once

#include "i_uart.hpp"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l476xx.h"
#include <cassert>
#include <span>

namespace hardware_layer
{
class Uart : public IUart
{
   public:
    enum class HardwareControl : std::uint32_t
    {
        None = UART_HWCONTROL_NONE,
        Rts = UART_HWCONTROL_RTS,
        Cts = UART_HWCONTROL_CTS,
        RtsCts = UART_HWCONTROL_RTS_CTS
    };

    enum class OneBitSample : std::uint32_t
    {
        Disable = UART_ONE_BIT_SAMPLE_DISABLED,
        Enable = UART_ONE_BIT_SAMPLE_ENABLE
    };

    enum class Mode : std::uint32_t
    {
        Rx = UART_MODE_RX,
        Tx = UART_MODE_TX,
        TxRx = UART_MODE_TX_RX
    };

    enum class Oversampling : std::uint32_t
    {
        Oversampling8 = UART_OVERSAMPLING_8,
        Oversampling16 = UART_OVERSAMPLING_16
    };

    enum class Parity : std::uint32_t
    {
        None = UART_PARITY_NONE,
        Even = UART_PARITY_EVEN,
        Odd = UART_PARITY_ODD
    };

    enum class StopBits : std::uint32_t
    {
        Bit_0_5 = UART_STOPBITS_0_5,
        Bit_1_0 = UART_STOPBITS_1,
        Bit_1_5 = UART_STOPBITS_1_5,
        Bit_2_0 = UART_STOPBITS_2
    };

    enum class WordLength : std::uint32_t
    {
        Length_7 = UART_WORDLENGTH_7B,
        Length_8 = UART_WORDLENGTH_8B,
        Length_9 = UART_WORDLENGTH_9B
    };

   private:
    UART_HandleTypeDef handler;

    GPIO_InitTypeDef gpioTx = {};
    GPIO_TypeDef* portTx = nullptr;

    GPIO_InitTypeDef gpioRx = {};
    GPIO_TypeDef* portRx = nullptr;

    RCC_PeriphCLKInitTypeDef periphClkInit = {};

    bool is_open = false;

   public:
    Uart(std::uint8_t instance);
    ~Uart();

    UART_HandleTypeDef* getHandler() { return &handler; }

    void open() override;
    void close() override;

    void startWrite(const std::span<std::uint8_t> data) override;

    void startRead(const std::span<std::uint8_t> data) override;

    bool isTxBusy();

    void configureBaudrate(std::uint32_t baudrate);
    void configure(Mode mode);
    void configure(OneBitSample enable);
    void configure(Oversampling oversampling);
    void configure(HardwareControl hardware_control);
    void configure(Parity parity);
    void configure(StopBits stop_bits);
    void configure(WordLength word_length);
};
}  // namespace hardware_layer
