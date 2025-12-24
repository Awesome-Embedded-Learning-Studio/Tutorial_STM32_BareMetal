#pragma once
#include <stdint.h>

namespace system_clock {


void system_clock_init();
/**
 * @brief delay the global system for given miliseconds
 * 
 * @param delay_ms 
 */
void system_delay_ms(uint32_t delay_ms);

/**
 * @brief delay the global system for given museconds
 * 
 * @param us 
 */
void system_delay_us(uint32_t us);

/**
 * @brief  provide the current frequency of system clock 
 * 
 * @return uint32_t , the raw Systicks Frequency
 */
uint32_t provide_application_sysfreq();
}


