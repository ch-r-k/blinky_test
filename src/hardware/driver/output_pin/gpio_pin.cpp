#include "gpio_pin.hpp"
#include <type_traits>
#include "stm32l4xx_hal_gpio.h"

GpioPin::GpioPin(Port init_port, Pin init_pin, Mode init_mode, Pull init_pull,
                 Speed init_speed)
{
    configure(init_port, init_pin, init_mode, init_pull, init_speed);
}

void GpioPin::configure(Port init_port, Pin init_pin, Mode init_mode,
                        Pull init_pull, Speed init_speed)
{
    port = init_port;
    pin = init_pin;
    mode = init_mode;
    pull = init_pull;
    speed = init_speed;

    GPIO_InitTypeDef gpio_init_struct;

    gpio_init_struct.Pin = static_cast<uint16_t>(pin);
    gpio_init_struct.Mode = static_cast<uint8_t>(mode);
    gpio_init_struct.Pull = static_cast<uint8_t>(pull);
    gpio_init_struct.Speed = static_cast<uint8_t>(speed);

    HAL_GPIO_Init(getPort(port), &gpio_init_struct);
}

void GpioPin::configure()
{
    GPIO_InitTypeDef gpio_init_struct;

    gpio_init_struct.Pin = static_cast<uint16_t>(pin);
    gpio_init_struct.Mode = static_cast<uint8_t>(mode);
    gpio_init_struct.Pull = static_cast<uint8_t>(pull);
    gpio_init_struct.Speed = static_cast<uint8_t>(speed);

    HAL_GPIO_Init(getPort(port), &gpio_init_struct);
}

void GpioPin::set()
{
    HAL_GPIO_WritePin(getPort(port), static_cast<uint16_t>(pin), GPIO_PIN_SET);
}

bool GpioPin::get()
{
    return HAL_GPIO_ReadPin(getPort(port), static_cast<uint16_t>(pin));
}

void GpioPin::reset()
{
    HAL_GPIO_WritePin(getPort(port), static_cast<uint16_t>(pin),
                      GPIO_PIN_RESET);
}

GPIO_TypeDef* GpioPin::getPort(Port port)
{
    switch (port)
    {
        case GpioPin::Port::PORT_A:
            return GPIOA;
            break;
        case GpioPin::Port::PORT_B:
            return GPIOB;
            break;
        case GpioPin::Port::PORT_C:
            return GPIOC;
            break;
        case GpioPin::Port::PORT_D:
            return GPIOD;
            break;
        case GpioPin::Port::PORT_E:
            return GPIOE;
            break;
        case GpioPin::Port::PORT_F:
            return GPIOF;
            break;
        case GpioPin::Port::PORT_G:
            return GPIOG;
            break;
        case GpioPin::Port::PORT_H:
            return GPIOH;
            break;

        default:
            return GPIOA;
            break;
    }
}