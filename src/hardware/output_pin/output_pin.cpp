#include "output_pin.hpp"
#include <type_traits>

OutputPin::OutputPin() {}

OutputPin::~OutputPin()
{
    HAL_GPIO_DeInit(getPort(port), static_cast<uint8_t>(pin));
}

void OutputPin::configure(Port init_port, Pin init_pin, Mode init_mode,
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

    HAL_GPIO_WritePin(getPort(port), static_cast<uint8_t>(pin), GPIO_PIN_SET);
    HAL_GPIO_Init(getPort(port), &gpio_init_struct);
}

void OutputPin::set()
{
    HAL_GPIO_WritePin(getPort(port), static_cast<uint16_t>(pin), GPIO_PIN_SET);
}

void OutputPin::reset()
{
    HAL_GPIO_WritePin(getPort(port), static_cast<uint16_t>(pin),
                      GPIO_PIN_RESET);
}

GPIO_TypeDef* OutputPin::getPort(Port port)
{
    switch (port)
    {
        case OutputPin::Port::PORT_A:
            return GPIOA;
            break;
        case OutputPin::Port::PORT_B:
            return GPIOB;
            break;
        case OutputPin::Port::PORT_C:
            return GPIOC;
            break;
        case OutputPin::Port::PORT_D:
            return GPIOD;
            break;
        case OutputPin::Port::PORT_E:
            return GPIOE;
            break;
        case OutputPin::Port::PORT_F:
            return GPIOF;
            break;
        case OutputPin::Port::PORT_G:
            return GPIOG;
            break;
        case OutputPin::Port::PORT_H:
            return GPIOH;
            break;

        default:
            return GPIOA;
            break;
    }
}