/*
   Blink Light.c
   6 LED lights can be controlled with led(number, state).  The number can
   be 0 to 5, and the state is ON or OFF.  The light numbers start at the
   top-right with 0, and increase clockwise, to 5 at the top-left.  So, 
   {0, 1, 2, 3, 4, 5} corresponds to lights labeled {P27, P26, P25, P15, 
   P16, P17}.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint(" BLINK\n  P27");                // Display
  while(1)                                   // Main loop
  {
    led(0, ON);                              // P27 light on
    pause(100);                              // For 0.1 s
    led(0, OFF);                             // P27 light off
    pause(100);                              // For 0.1 s
  }    
}


