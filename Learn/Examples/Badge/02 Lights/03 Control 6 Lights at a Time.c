/*
   Control 6 Lights at a Time.c
   Uses binary digits to control lights.  This 0b101010 turns on lights 
   5, 3, and 1, and turns off 4, 2, and 0.  Another way to think about it
   is that it turns on the P17, P15, and P26 lights and turns off the P16,
   P25 and P27 lights.  Conversely, 0b010101turns on 4, 2, and 0 and turns 
   off 5, 3, and 1. That's P16, P25, P27 on, and P17, P15, and P26 off.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("  BITS");                       // Display text
  screen_auto(OFF);                          // Auto-update off
  while(1)                                   // Main loop
  {
    cursor(0, 1);                            // Column 0, line 1
    oledprint("0b101010");                   // Prep binary value
    screen_update();                         // Copy to display
    
    leds(0b101010);                          // Same value sets LEDs
    pause(250);                              // Wait 0.25 s

    cursor(0, 1);                            // Reposition cursor
    oledprint("0b010101");                   // Update binary value
    screen_update();                         // ...and display

    leds(0b010101);                          // Same value sets LEDs again
    pause(250);                              // ...for another 0.25 s
  }    
}


