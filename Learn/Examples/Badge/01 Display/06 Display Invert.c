/*
   Display Invert.c
   Makes white pixels black and vice-versa.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    oledprint("  True  ");                   // True (black background)
    pause(2000);                             // Wait 2 s
    clear();                                 // Clear the screen
    invert(1);                               // Set invert
    oledprint("Inverted");                   // Display w/ white background
    pause(2000);                             // Wait 2 s
    clear();                                 // Clear again
    invert(0);                               // Back to true
  }
}


