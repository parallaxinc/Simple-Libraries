/*
   Blink Lights.c
   Use a variable as an index to repeatedly select a sequence of lights
   for turning on/off.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int n = 0;                                   // Number

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("n=012345repeats");              // Display
  // n increments, and is used to select
  // which light number is turned on/off.
  while(1)                                   // Main loop
  {
    led(n, ON);                              // Turn on light n
    pause(100);                              // ...for 0.1 s
    led(n, OFF);                             // Turn off light n
    pause(100);                              // ...for 0.1s
    n++;                                     // Increment n
    if(n == 6) n = 0;                        // Reset if > 5
  }    
}


