/**
 * @file switch_password_pattern.c
 * @brief Detailed documentation and description for this program can be found in: switch_password_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000
#define MEMORY_ADDRESS_SWITCH 0xff200040

// State machine function implementing a sequential switch password combination lock
int passwordtest() {
    // Pointer to the memory-mapped slide switches hardware register
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SWITCH;
    
    // Static state tracker preserving state between function calls
    static int state = 1; 

    switch (state) {
        case 1: 
            // Check for first combination code step
            if (*switch_byte_ptr == 0x00000010) {
                state = 2; 
            } else if (*switch_byte_ptr != 0x00000000) {
                state = 1; 
            }
            break;
            
        case 2: 
            // Check for second combination code step
            if (*switch_byte_ptr == 0x00000018) {
                state = 3;
            } else if (*switch_byte_ptr != 0x00000010) {
                state = 1;
            }
            break;
            
        case 3: 
            // Check for third combination code step
            if (*switch_byte_ptr == 0x0000001c) {
                state = 4;
            } else if (*switch_byte_ptr != 0x00000018) {
                state = 1;
            }
            break;
            
        case 4: 
            // Check for final combination step to unlock (returns 1 on success)
            if (*switch_byte_ptr == 0x0000001e) {
                return 1; 
            } else if (*switch_byte_ptr != 0x0000001c) {
                state = 1;
            }
            break;
    }

    return 0; // Returns 0 while locked or progressing
}

int main(void) {
    // Pointer to the memory-mapped hardware LEDs register[cite: 1]
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    *led_byte_ptr = 0x0; // Initialize LEDs to OFF[cite: 1]
    
    while(1) {
        // Continuously check password state machine; light up all LEDs if unlocked, else keep them OFF[cite: 1]
        if (passwordtest()) {
            *led_byte_ptr = 0x3ff;
        } else {
            *led_byte_ptr = 0x0;   
        }
    }
}