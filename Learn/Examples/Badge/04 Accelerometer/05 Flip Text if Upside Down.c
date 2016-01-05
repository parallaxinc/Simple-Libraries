/*
   Flip Text if Upside Down.c
   Detect when tilted upside-down and rotate the screen 180 for viewing.
   Screen auto-update is disabled since writing text and rotating it is two
   steps, but the final result is all that should be visible.  
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int y;                                       // Y-axis variable

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  screen_auto(OFF);                          // Disable screen auto-update
  while(1)                                   // Main loop
  {
    y = accel(AY);                           // Get y tilt

    cursor(0, 0);                            // Start setting up display
    oledprint("y = %03d ", y);
    cursor(0, 1);
    oledprint("        ", y);

    if(y < -40)                              // If tilt < -40, rotate it
    {
      rotate180();
    }                  

    screen_update();                         // Now copy screen buffer to screen
    pause(20);
  }    
}


