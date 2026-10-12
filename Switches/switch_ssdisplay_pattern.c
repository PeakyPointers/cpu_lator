/**
 * @file switch_ssdisplay_pattern.c
 * @brief Detailed documentation and description for this program can be found in: switch_ssdisplay_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000
#define MEMORY_ADDRESS_SSDISPLAY 0xff200020
#define MEMORY_ADDRESS_SWITCH 0xff200040
    
// Helper function using a structured switch-case with a single return point to map digits (0-9) to 7-segment hex values
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
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SWITCH;
    int k = 0; // Loop counter for iterating through switch pins
    
    while(1)
    {
        int Total = 0; // Reset total accumulator for each polling cycle
        
        // Compact loop checking all 10 switches dynamically using bitwise shifting (`1 << k`)
        for(k = 0; k < 10; k++){
            if((*switch_byte_ptr & (uint32_t)(1 << k)) == (uint32_t)(1 << k)){
                Total += k; // Add switch index weight if the switch is active
            }
        }

        // Send the final accumulated total value to the 7-segment display function
        ssdislay(Total);
    }
}