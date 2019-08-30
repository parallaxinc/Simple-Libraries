/*
   Box and Lines.c
   Box and line functions have parameters of xi, yi, xf, yf, color.  
   Valid x ranges are 0 to 127, and valid y ranges are 0 to 63.  These
   pixel counts are measured from the top-left.  The color is just one 
   bit, with 1 indicating white and 0 black.  Pixel counts are measured 
   from the top-left.   
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int x, y;

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  box(32, 16, 96, 48, 1);                    // box (32, 16)...(96, 48)
  line(32, 16, 96, 48, 1);                   // Line diagonal in box
  pause(500);                                // Wait 1/2 s
  line(32, 48, 96, 16, 1);                   // Other diagonal
}  
