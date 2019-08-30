/*
   RGB LEDs.c
   Uses rgb(side, color) to control L or R leds, with color options of OFF, 
   BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, and WHITE.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("RGB LEDs");                     // Display text 
  oledprint("L      R");                     // Sides 
  while(1)                                   // Main loop
  {
    rgb(L, YELLOW);                          // Left, yellow
    rgb(R, BLUE);                            // Right, blue
    pause(400);                              // ...for 4/10 s
    rgb(L, RED);                             // and so on...
    rgb(R, WHITE);
    pause(400);
    rgb(L, WHITE);
    rgb(R, GREEN);
    pause(400);
  }    
}


