#pragma once
#include <stm32f1xx_hal.h>

// 枚举端口
enum class PortName
{
    A,
    B,
    C
};

// 编译期函数，返回 GPIO_TypeDef*

enum class Mode
{
    Input,
    Output
};
enum class Pull
{
    None,
    Up,
    Down
};

template <PortName Port, uint16_t Pin> class GPIO
{
public:
    static GPIO_TypeDef *getPort(PortName port)
    {
        switch (port) {
            case PortName::A:
                return GPIOA;
            case PortName::B:
                return GPIOB;
            case PortName::C:
                return GPIOC;
        }
        return nullptr; // 不会发生
    }
    static void init(Mode mode, Pull pull = Pull::None)
    {
        GPIO_TypeDef *port = getPort(Port);

        // 使能端口时钟
        if (Port == PortName::A)
            __HAL_RCC_GPIOA_CLK_ENABLE();
        else if (Port == PortName::B)
            __HAL_RCC_GPIOB_CLK_ENABLE();
        else if (Port == PortName::C)
            __HAL_RCC_GPIOC_CLK_ENABLE();

        GPIO_InitTypeDef gpioInit{};
        gpioInit.Pin = Pin;

        if (mode == Mode::Output) {
            gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
            gpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
        }
        else {
            gpioInit.Mode = GPIO_MODE_INPUT;
            if (pull == Pull::Up)
                gpioInit.Pull = GPIO_PULLUP;
            else if (pull == Pull::Down)
                gpioInit.Pull = GPIO_PULLDOWN;
            else
                gpioInit.Pull = GPIO_NOPULL;
        }

        HAL_GPIO_Init(port, &gpioInit);
    }

    static void set() { getPort(Port)->BSRR = Pin; }
    static void reset() { getPort(Port)->BRR = Pin; }
    static void toggle()
    {
        if (read())
            reset();
        else
            set();
    }
    static bool read() { return (getPort(Port)->IDR & Pin) != 0; }
};
