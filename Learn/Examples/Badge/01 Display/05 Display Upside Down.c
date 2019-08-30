/*
   Display Upside Down.c
   Rotating the display 180-degrees can be convenient when holding the 
   badge upside down.  Note that auto-update is turned off to allow the 
   message to be started right-side up first, then rotated.  After those 
   two steps, it's ready and made visible with screen_update.    
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("right-  side up");              // Up message
  pause(2000);                               // Wait 2 s
  clear();                                   // Clear the screen
  screen_auto(OFF);                          // Turn off auto-update
  oledprint("upside  down");                 // Display new message
  rotate180();                               // Rotate the image
  screen_update();                           // Make it visible
  pause(2000);                               // Wait 2 s
  clear();                                   // Back to right-side up 
  screen_auto(ON);                           // Resume auto-update
  oledprint("right-  side up");              // Last message
}


