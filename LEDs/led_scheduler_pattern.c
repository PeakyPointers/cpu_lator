/**
 * @file led_scheduler_pattern.c
 * @brief Detailed documentation and description for this program can be found in: led_scheduler_pattern.txt in the same folder
 */

#include <stdint.h>
#include <stdbool.h>
    
#define MEMORY_ADDRESS_LED 0xff200000
    
// Volatile pointer to directly access the hardware LED register without compiler optimization caching
volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    
// Task executed every 1 millisecond (Tick 1)
int task_1ms(void){
    // Toggle the 0th LED using XOR bitwise operation
    *led_byte_ptr = *led_byte_ptr ^ (0x00000001);   
    return 0;
}

// Task executed every 10 milliseconds (Tick 10)
int task_10ms(void){
    // Toggle the 1st LED using XOR bitwise operation
    *led_byte_ptr = *led_byte_ptr ^ (0x00000002);   
    return 0;
}

// Task executed every 100 milliseconds (Tick 100)
int task_100ms(void){
    // Toggle the 2nd LED using XOR bitwise operation
    *led_byte_ptr = *led_byte_ptr ^ (0x00000004);   
    return 0;
}

// Task executed every 1000 milliseconds / 1 second (Tick 1000)
int task_1000ms(void){
    // Toggle the 3rd LED using XOR bitwise operation
    *led_byte_ptr = *led_byte_ptr ^ (0x00000008);       
    return 0;
}

// Cooperative scheduler loop managing multi-rate task execution timing
void scheduler()
{
    int i = 0;
    while(1)
    {   
        // Increment tick counter on each loop iteration (assumes ~1ms per loop)
        i++;
        
        // Run 1ms task every single loop iteration
        task_1ms();
        
        // Run 10ms task every 10 iterations using modulo arithmetic
        if(i % 10 == 0)
        {
            task_10ms();
        }
        
        // Run 100ms task every 100 iterations
        if(i % 100 == 0)
        {
            task_100ms();
        }

        // Run 1000ms task every 1000 iterations, then reset counter
        if(i % 1000 == 0)
        {
            task_1000ms();
            i = 0; // Reset tick counter to prevent overflow
        }
    }
}

int main(void){
        // Launch the cooperative scheduler (assuming loop execution takes 1ms)
        scheduler();
}