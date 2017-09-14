/*
   Check X and Y axes.c
   With the badge held flat, X is left/right tilt, Y is away from and toward 
   you tilt.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y;                                    // X & Y axis variables

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    x = accel(AX);                           // Get accelerometer values 
    y = accel(AY);
    
    cursor(0, 0);                            // Display
    oledprint("x = %03d ", x);
    cursor(0, 1);
    oledprint("y = %03d ", y);

    pause(20);                               // Wait 1/50 s before repeat
  }    
}


