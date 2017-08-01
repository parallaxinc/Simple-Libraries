/*
   Both RGBs with 1 Call.c
   Instead of picking between L and R, the rgbs function sets the left and
   right colors with a single call.  The RGB colors are actually constants
   BLUE (1), GREEN (2), CYAN (3), RED (4), MAGENTA (5), YELLOW (6), WHITE(7).
   So, a for... loop can also be used to index through each color.   
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int n = 0;                                   // Number

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("One CallTwo RGBs");              

  rgbs(YELLOW, BLUE);                        // Left yellow, right blue
  pause(500);
  rgbs(WHITE, GREEN);
  pause(500);
  
  while(1)                                   // RGB color loop
  {
    for(int n = OFF; n < WHITE*2; n++)       // Count through colors
    {
      rgbs(n, 8-n);                          // L counts up, R down
      pause(500);                            // 1/2 s delay
    }      
  }    
}


