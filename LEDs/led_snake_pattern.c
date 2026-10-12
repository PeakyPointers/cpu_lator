/**
 * @file led_snake_pattern.c
 * @brief Detailed documentation and description for this program can be found in: led_snake_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000

/**
 * @brief Creates a software delay using a dummy assembly loop.
 * @param msec Delay time in milliseconds.
 */
int delayms(int msec){
    int j = 0;
    for(j = 1; j < msec * 1000; j++){
        // 'nop' stands for No Operation; it just wastes a clock cycle
        __asm__ volatile("nop");
    }
    return 0;
}

int main(void)
{
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    int i = 0;
    int sec = 1; // 1-second interval delay
    
    // Starting with an initial LED pattern state
    *led_byte_ptr = 0x3bf;
    delayms(sec * 1000);
    
    while(1)
    {
        // Turning OFF LEDs sequentially using bitwise shift operations
        for (i = 1; i <= 10; i++){
            *led_byte_ptr = (0x3bf << i);
            delayms(sec * 1000);
        }

        // Turning ON LEDs sequentially with custom pattern logic
        for (i = 1; i <= 10; i++){
            if(i != 4){
                *led_byte_ptr = (*led_byte_ptr << 1) + 1;
                delayms(sec * 1000);
            }
            else{
                *led_byte_ptr = 0xe;
                delayms(sec * 1000);
            }
        }
    }
}