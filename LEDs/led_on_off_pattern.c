/**
 * @file led_on_off_pattern.c
 * @brief Detailed documentation and description for this program can be found in: led_on_off_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS 0xff200000

/**
 * @brief Creates a software delay using a dummy assembly loop.
 * @param ms Delay time in milliseconds.
 */
void delay(int ms)
{
    int j;
    for (j = 0; j < ms * 1000; j++)
    {
        // 'nop' stands for No Operation; it just wastes a clock cycle
        __asm__ volatile("nop");
    }
}

int main(void)
{
    int i, k;
    int msec = 500; // Half-second delay for clear visibility

    // Pointer pointing directly to the hardware memory address of the LEDs
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS;
    
    while(1)
    {
        // Progressively turn on LEDs one by one up to 10
        for(i = 1; i <= 10; i++)
        {
            *led_byte_ptr = (1 << i) - 1;
            delay(msec);
        }
        
        // Progressively step down the LEDs from 10 back to 0
        for(k = 10; k >= 0; k--)
        {
            *led_byte_ptr = (1 << k) - 1;
            delay(msec);
        }
    }
}