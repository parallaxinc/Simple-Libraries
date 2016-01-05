/*
   Check Two Buttons.c
   Displays states of buttons by P27 (index = 0) and P25 (index = 2).
   Uses those states to control adjacent LEDs.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int state27, state25;                        // For storing button states

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    state27 = button(0);                     // Get button states
    state25 = button(2);

    cursor(0, 0);                            // Display button states
    oledprint("P27 = %d ", state27);
    oledprint("P25 = %d ", state25);

    if(state27 == 1)                         // Control adjacent lights
    {
      led(0, ON);
    }
    else
    {
      led(0, OFF);
    }            
    if(state25 == 1)
    {
      led(2, ON);
    }
    else
    {
      led(2, OFF);
    }            
  }    
}


