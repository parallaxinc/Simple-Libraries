/*
  Cog Run Example.c
  
  Run function that blinks a light with another cog for 3 seconds, then end
  that process.

  http://learn.parallax.com/propeller-c-multicore_approaches/simple-multicore
*/

#include "simpletools.h"                      // Library include

void blink();                                 // Forward declaration
int *cog;                                     // For storing process ID

int main()                                    // Main function
{
  cog = cog_run(&blink, 10);                  // Run blink in other cog
  pause(3000);                                // ...for 3 seconds
  cog_end(cog);                               // then stop the cog
}

void blink()                                  // Blink function for other cog
{
  while(1)                                    // Endless loop for other cog
  {
    high(26);                                 // P26 LED on
    pause(100);                               // ...for 0.1 seconds
    low(26);                                  // P26 LED off
    pause(100);                               // ...for 0.1 seconds
  }
}
