/*
   Held Steady vs Shaken.c
   Detecting a shaking event can take lots of code, but the accelerometer
   chip can check automatically.  To find out if the badge is being shaken,
   simply use the accel_shaken function.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int shaken;                                  // Shaken variable

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  
  while(1)                                   // Main loop
  {
    shaken = accel_shaken();                 // Check if shaken
    cursor(0, 0);                            // Display if shaken
    if(shaken == 1)
    {
      oledprint("          Shaken");
      pause(500);
    }
    else
    {
      oledprint("Steady          ");
    }      
    pause(20);
  }    
}

