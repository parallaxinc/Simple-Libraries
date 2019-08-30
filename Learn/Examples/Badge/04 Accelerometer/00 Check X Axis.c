/*
   Check X Axis.c
   Displays acceleration/tilt measured on the acceleromteer's X-axis.  
   Hold badge flat and tilt left/right to see the measurement change.
   +/- 100 -> +/- 1 g
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x;                                       // X-axis variable

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("LR Tilt");                      // Heading
  while(1)                                   // Main loop
  {
    x = accel(AX);                           // Get x acceleration/tilt
    
    cursor(0, 1);                            // Display 
    oledprint("x = %03d ", x);               // Display tilt value

    pause(20);                               // Wait 1/50 s
  }    
}
