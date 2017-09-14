/*
   Another Blink Sequence.c
   Instead of turning each light on/off in the same loop repetition, this
   example turns all on with one loop, then all off with a different loop.
   The extra space after oledprint ON is to overwrite the second F in OFF
   (otherwise it would display ONF as the first loop repeats a second time).
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int n = 0;                                   // Number

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  while(1)                                   // Main loop
  {
    cursor(0, 0);                            // Cursor to 0
    oledprint("  ON ");                      // Display ON message
    for(int n = 0; n < 6; n++)               // Count 0 to 5
    {
      led(n, ON);                            // 0 to 5 lights on
      cursor(0, 1);                          // Cursor 2nd line
      oledprint(" n = %d", n);               // Display n value
      pause(400);                            // Wait 4/10 s
    }
    cursor(0, 0);                            // Cursor to top-left
    oledprint("  OFF");                      // Display OFF message
    for(int n = 0; n < 6; n++)               // Count 0 to 5 again
    {
      led(n, OFF);                           // Turn off each LED
      cursor(0, 1);                          // Position cursor 2nd line
      oledprint(" n = %d", n);               // Display n
      pause(400);                            // Wait 4/10 s
    }
  }
}      
    
