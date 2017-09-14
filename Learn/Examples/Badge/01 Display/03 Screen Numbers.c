/*
   Screen Numbers.c
   Use formatting flags to make oledprint display values. %d, %f, %x, %b
   are supported.  Leading zero and space padding are also supported.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("SECONDS");                      // Heading
  for(int i = 1; i <= 10; i++)               // Count 1 to 10
  {
    cursor(3, 1);                            // Cursor -> col 3, row 1
    oledprint("%02d", i);                    // Display 2-digit integer value
    pause(1000);                             // Pause 1 second
  }
  clear();                                   // Clear the screen
  oledprint("   All    Done!");              // Display done
}


