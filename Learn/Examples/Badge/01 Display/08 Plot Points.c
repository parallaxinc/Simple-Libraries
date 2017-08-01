/*
   Plot Points.c
   The point function has parameters of (x, y, color).  X increases from
   0 (left) to 127 (right).  Y increases from 0 (top) to 64 (botton).  Color
   is 1 for white, 0 for black.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y;                                    // X and Y variables

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    for(x = 0; x <= 120; x+=8)               // Count 0 to 120
    {
      y = 64 - (x/2);                        // y = x/2
      point(x, y, 1);                        // Plot white point
      pause(20);                             // Wait 1/50 s
    }
    pause(500);                              // Wait 1/2 s
    for(x = 120; x >= 0; x-=8)               // Count in reverse
    {
      y = 64 - (x/2);                        // Same function
      point(x, y, 0);                        // Plot black point
      pause(20);                             // Wait 1/50 s
    }
    pause(200);                              // Wait 1/5 s
  }
}  
