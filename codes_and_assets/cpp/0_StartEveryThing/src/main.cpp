#include "gpio/gpio.hpp"
#include "stm32f1xx_hal.h"
#include "system_clock/system_clock.h"

int main()
{
    HAL_Init();

    using Led = GPIO<PortName::C, GPIO_PIN_13>;

    Led::init(Mode::Output);

    while (1) {
        Led::toggle();
        HAL_Delay(200);
    }
}
