/*
   Shift Display.c
   Use a couple of the display's automatic image shifting features.
   Although it should be possible to select which parts to shift from 
   15 slices of screen, currently only the (0, 15) entire screen setting 
   appears to work as expected. 
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint(" BANNER   TEXT");               // Something to shift
  screen_scrollRight(0, 15);                 // Scroll left-right
  pause(9200);                               // For 9.2 s
  screen_scrollLeft(0, 15);                  // Reverse direction
  pause(9200);                               // & go for another 9.2
  screen_scrollStop();                       // Stop
}


