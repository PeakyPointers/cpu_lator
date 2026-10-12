/**
 * @file switch_ssdisplay_pattern.c
 * @brief Detailed documentation and description for this program can be found in: switch_ssdisplay_pattern.txt in the same folder
 */

#include <stdint.h>

#define MEMORY_ADDRESS_LED 0xff200000
#define MEMORY_ADDRESS_SSDISPLAY 0xff200020
#define MEMORY_ADDRESS_SWITCH 0xff200040
    
// Helper function to map integer values (0-9) to their corresponding 7-segment display hex bit patterns
int numbtossd(int numb){
    if(numb == 0){
        return 0x3F;
        }
    if(numb == 1){
        return 0x06;
        }
    if(numb == 2){
        return 0x5B;
        }
    if(numb == 3){
        return 0x4F;
        }
    if(numb == 4){
        return 0x66;
        }
    if(numb == 5){
        return 0x6D;
        }
    if(numb == 6){
        return 0x7D;
        }
    if(numb == 7){
        return 0x07;
        }
    if(numb == 8){
        return 0x7F;
        }
    if(numb == 9){
        return 0x6F;
        }
    return 0x00; // Default fallback return
}

// Function to split the total numeric value into digits and write them to the 7-segment display hardware register
void ssdislay(int total)
{
    //int temp = total;
    volatile uint32_t *ssdisplay_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SSDISPLAY;
    int units = total % 10;
    int tens = (total / 10) % 10;
    
    // Shift tens display value and pack it with units into the hardware register
    *ssdisplay_byte_ptr = (uint32_t)((numbtossd(tens) << 8) | numbtossd(units));
}


int main(void)
{
    // Individual switch state flags and the final calculated total value
    int Zero = 0, One = 0, Two = 0, Three = 0, Four = 0, Five = 0, Six = 0, Seven = 0, Eight = 0, Nine = 0, Total = 0;
    
    // Pointers to the memory-mapped hardware registers for LEDs and switches
    volatile uint32_t *led_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_LED;
    volatile uint32_t *switch_byte_ptr = (volatile uint32_t *)MEMORY_ADDRESS_SWITCH;
    
    while(1)
    {
        // Check state of the 0th switch via bitwise AND mask
        if((*switch_byte_ptr & (uint32_t)(0x00000001)) == (uint32_t)(0x00000001)){
            Zero = 1;
        }
        else{
            Zero = 0;
        }
        
        // Check state of the 1st switch
        if((*switch_byte_ptr & (uint32_t)(0x00000002)) == (uint32_t)(0x00000002)){
            One = 1;
        }
        else{
            One = 0;
        }
        
        // Check state of the 2nd switch
        if((*switch_byte_ptr & (uint32_t)(0x00000004)) == (uint32_t)(0x00000004)){
            Two = 1;
        }
        else{
            Two = 0;
        }
        
        // Check state of the 3rd switch
        if((*switch_byte_ptr & (uint32_t)(0x00000008)) == (uint32_t)(0x00000008)){
            Three = 1;
        }
        else{
            Three = 0;
        }
        
        // Check state of the 4th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000010)) == (uint32_t)(0x00000010)){
            Four = 1;
        }
        else{
            Four = 0;
        }
        
        // Check state of the 5th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000020)) == (uint32_t)(0x00000020)){
            Five = 1;
        }
        else{
            Five = 0;
        }
        
        // Check state of the 6th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000040)) == (uint32_t)(0x00000040)){
            Six = 1;
        }
        else{
            Six = 0;
        }
        
        // Check state of the 7th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000080)) == (uint32_t)(0x00000080)){
            Seven = 1;
        }
        else{
            Seven = 0;
        }
        
        // Check state of the 8th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000100)) == (uint32_t)(0x00000100)){
            Eight = 1;
        }
        else{
            Eight = 0;
        }
        
        // Check state of the 9th switch
        if((*switch_byte_ptr & (uint32_t)(0x00000200)) == (uint32_t)(0x00000200)){
            Nine = 1;
        }
        else{
            Nine = 0;
        }
        
        // Calculate the weighted total score based on active switch states
        Total = 0 * Zero + 1 * One + 2 * Two + 3 * Three + 4 * Four + 5 * Five + 6 * Six + 7 * Seven + 8 * Eight + 9 * Nine;
        
        // Output the computed total value to the 7-segment displays
        ssdislay(Total);
    }
}