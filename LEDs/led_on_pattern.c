/**
 * @file led_on_pattern.c
 * @brief Detailed documentation and description for this program can be found in: led_on_pattern.txt in the same folder
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
    int i;
    int msec = 2000; // Initial start delay of 2 seconds

    // Pointer pointing directly to the hardware memory address of the LEDs
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS;
    
    while(1)
    {
        for(i = 1; i <= 10; i++)
        {
            // Light up LEDs sequentially using bit shift
            *led_byte_ptr = (1 << i) - 1;
            
            // Speed up the sequence by decreasing the delay incrementally
            msec -= 200;
            delay(msec);
        }
        
        // Reset delay back to initial value for the next cycle loop
        msec = 2000;
    }
}