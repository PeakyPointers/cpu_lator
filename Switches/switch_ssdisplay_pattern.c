/**
 * @file switch_ssdisplay_pattern.c
 * @brief Detailed documentation and description for this program can be found in: switch_ssdisplay_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000
#define MEMORY_ADDRESS_SSDISPLAY 0xff200020
#define MEMORY_ADDRESS_SWITCH 0xff200040
    
// Helper function utilizing a switch-case block to map numbers (0-9) to 7-segment display hex bit patterns
int numbtossd(int numb){
    switch(numb){
    case 0: return 0x3F;
    case 1: return 0x06;
    case 2: return 0x5B;
    case 3: return 0x4F;
    case 4: return 0x66;
    case 5: return 0x6D;
    case 6: return 0x7D;
    case 7: return 0x07;
    case 8: return 0x7F;
    case 9: return 0x6F;
    default: return 0x00;
    }
}

// Function to split the total numeric value into digits and write them to the 7-segment display register
void ssdislay(int total)
{
    // Pointer to the memory-mapped 7-segment display hardware register
    volatile uint32_t *ssdisplay_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SSDISPLAY;
    int units = total % 10;
    int tens = (total / 10) % 10;
    
    // Shift the tens display value and pack it together with the units into the hardware register
    *ssdisplay_byte_ptr = (uint32_t)((numbtossd(tens) << 8) | numbtossd(units));
}


int main(void)
{
    // Pointer to the memory-mapped slide switches hardware register
    // volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SWITCH;
    
    while(1)
    {
        int Total = 0; // Reset total accumulator for each polling cycle
        
        // Check state of the 0th switch and add its weighted value if active
        if((*switch_byte_ptr & (uint32_t)(0x00000001)) == (uint32_t)(0x00000001)){
            Total += 0;
        }
        
        // Check state of the 1st switch
        if((*switch_byte_ptr & (uint32_t)(0x00000002)) == (uint32_t)(0x00000002)){
            Total += 1;
        }
        
        // Check state of the 2nd switch
        if((*switch_byte_ptr & (uint32_t)(0x00000004)) == (uint32_t)(0x00000004)){
            Total += 2;
        }
        
        // Check state of the 3rd switch
        if((*switch_byte_ptr & (uint32_t)(0x00000008)) == (uint32_t)(0x00000008)){
            Total += 3;
        }
        
        // Check state of the 4th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000010)) == (uint32_t)(0x00000010)){
            Total += 4;
        }
        
        // Check state of the 5th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000020)) == (uint32_t)(0x00000020)){
            Total += 5;
        }

        // Check state of the 6th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000040)) == (uint32_t)(0x00000040)){
            Total += 6;
        }
        
        // Check state of the 7th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000080)) == (uint32_t)(0x00000080)){
            Total += 7;
        }
        
        // Check state of the 8th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000100)) == (uint32_t)(0x00000100)){
            Total += 8;
        }

        // Check state of the 9th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000200)) == (uint32_t)(0x00000200)){
            Total += 9;
        }

        // Send the final accumulated total value to the 7-segment display function
        ssdislay(Total);
    }
}