/*
   Check XYZ with One Call.c
   BE CAREFUL with accels, you must pass the addresses of the variables
   you want it to store tilt/acceleration measurements in, not the values.
   In other words, use &x, &y, &z, not x, y, z.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y, z;                                 // Axis variables

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint(" 3-Axis ");                     
  text_size(SMALL);

  while(1)                                   // Main loop
  {
    accels(&x, &y, &z);                      // Get all 3 acceleration/tilts
    
    cursor(5, 4);                            // Display all 3 values
    oledprint("x = %3d " , x);
    cursor(5, 5);
    oledprint("y = %3d ", y);
    cursor(5, 6);
    oledprint("z = %3d ", z);
    pause(100);

    pause(20);
  }    
}


