/*
   Plot Parabola.c
   Plot y = x^2 / 256 the from 0 to 127.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y;

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    for(x = 0; x < 128; x++)                 // Count 0 to 127
    {
      y = 64 - (x*x/256);                    // Calculate y
      point(x, y, 1);                        // Plot white point
      pause(2);                              // Wait 2 ms
    }
    pause(500);                              // Wait 5 s
    for(x = 127; x > 0; x--)                 // Count 127 to 0
    {
      y = 64 - (x*x/256);                    // Calculate y
      point(x, y, 0);                        // Plot black point
      pause(2);                              // Wait 2 ms
    }
  }
}  
