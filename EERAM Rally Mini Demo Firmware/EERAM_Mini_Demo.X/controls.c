#include "controls.h"

// number of milliseconds between button checks
#define INTERVAL    10

volatile uint8_t buttons = 0;
volatile uint8_t debounceTicks = 0;

// read the DPad and Action buttons
uint8_t readButtons(void)
{
    uint8_t portRead = 0;
    portRead = PORTC & ALL_KEY_MASK;
    
    // because the buttons register as logic low and the rest of the program
    // responds to logic high the DPad button presses need to be inverted
    portRead ^= ALL_KEY_MASK;   
    
    if(0 == A_PORT)
    {
        portRead |= KEY_A;
    }
    
    if(0 == B_PORT)
    {
        portRead |= KEY_B;
    }
    
    return portRead;
}

void debounceButtons(void)
{
    buttons = 0;
    
   // if(1 == debounceTicks)
   // {
        buttons = readButtons();
   // }
   
   // if(INTERVAL == debounceTicks)
   // {
   //     buttons = readButtons();
   //     debounceTicks = 0;
   // }
    
    //debounceTicks++;
}

uint8_t checkButtons(void)
{
    return buttons;
}

     