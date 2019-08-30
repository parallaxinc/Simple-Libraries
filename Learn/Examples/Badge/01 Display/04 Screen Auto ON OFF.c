/*
   Screen Auto ON OFF.c
   Turn automatic screen update off to make multiple updates to the screen
   buffer before allowing the changes to appear.  The screen_update function
   can be used to manually update when changes are ready.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  for(int n = 0; n < 8; n++)                 // Count 0 to 8
  {
    oledprint("%d", n);                      // Update with each number
    pause(200);                              // Pause 1/5 s
  }
  screen_auto(OFF);                          // Disable screen auto-update
  cursor(0, 1);                              // Position cursor

  // Changes in this loop don't appear
  //  until the screen_update call.
  for(int n = 'a'; n <= 'h'; n++)            // Count from a to h
  {                                       
    oledprint("%c", n);                      // Print the character
    pause(200);                              // Wait 1/5 s
  }
  screen_update();                           // Make changes appear
}  
