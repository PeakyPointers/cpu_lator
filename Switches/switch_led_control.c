/**
 * @file switch_led_control.c
 * @brief Detailed documentation and description for this program can be found in: switch_led_control.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000
#define MEMORY_ADDRESS_SWITCH 0xff200040

int main(void)
{
    // volatile uint32_t switch_temp;
    
    // Pointer pointing directly to the hardware memory address of the LEDs
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    
    // Pointer pointing directly to the hardware memory address of the switches
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SWITCH;
    
    // Continuously read switches and mirror their states to the LEDs in real-time
    while(1)
    {
        *led_byte_ptr = *switch_byte_ptr;
    }
}