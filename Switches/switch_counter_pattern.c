/**
 * @file switch_counter_pattern.c
 * @brief Detailed documentation and description for this program can be found in: switch_counter_pattern.txt in the same folder
 */

#include <stdint.h>
    
#define MEMORY_ADDRESS_SWITCH 0xff200040
#define MEMORY_ADDRESS_SSDISPLAY 0xff200020
    
// Helper function using a structured switch-case to map digits (0-9) to 7-segment display hex bit patterns
int numbtossd(int numb){
    int numret;
    switch(numb){
    case 0: numret = 0x3F; break;
    case 1: numret = 0x06; break;
    case 2: numret = 0x5B; break;
    case 3: numret = 0x4F; break;
    case 4: numret = 0x66; break;
    case 5: numret = 0x6D; break;
    case 6: numret = 0x7D; break;
    case 7: numret = 0x07; break;
    case 8: numret = 0x7F; break;
    case 9: numret = 0x6F; break;
    default: numret = 0x00;
    }
    return numret;
}

// Function to split the numeric value into units, tens, and hundreds places and pack them into the 7-segment register
void ssdisplay (int ssdnum){
    // Pointer to the memory-mapped 7-segment display hardware register
    volatile uint32_t *ssdisplay_byte_ptr = (volatile uint32_t*)MEMORY_ADDRESS_SSDISPLAY;
    int units = ssdnum % 10;
    int tens = (ssdnum / 10) % 10;
    int hundreds = (ssdnum / 100) % 10;
    
    // Pack units, shifted tens, and shifted hundreds bit patterns into the display hardware register
    *ssdisplay_byte_ptr = numbtossd(units) | (numbtossd(tens) << 8) | (numbtossd(hundreds) << 16);
}

int main(void){
    // Pointer to the memory-mapped slide switches hardware register
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t*)MEMORY_ADDRESS_SWITCH;
    int switch_st_last = 0;   // Stores previous state of the increment switch for edge detection
    int switch_st_lat = 0;    // Stores current sampled state of the increment switch
    int switch_st_reset = 0;  // Stores state of the reset switch
    int i = 0;                // Counter variable
    
    ssdisplay(i); // Initialize display to show 0
    
    while(1){
        // Sample current state of switch 0 (increment) and switch 1 (reset)
        switch_st_lat = ((*switch_byte_ptr & (uint32_t)0x00000001) != (uint32_t)0x00000000);
        switch_st_reset = ((*switch_byte_ptr & (uint32_t)0x00000002) != (uint32_t)0x00000000);
        
        // Detect rising edge (transition from LOW/0 to HIGH/1) on the increment switch
        if((switch_st_lat == 1) && (switch_st_last == 0)){
            i++;          // Increment counter value
            ssdisplay(i); // Update 7-segment display output
        }
        
        // Save current switch state as last state for the next loop iteration
        switch_st_last = switch_st_lat;
        
        // Check if reset switch is active to clear the counter back to zero
        if(switch_st_reset){
            i = 0;
            ssdisplay(i);
        }
    }
}