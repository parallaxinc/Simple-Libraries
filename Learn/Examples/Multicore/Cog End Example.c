/*
  Cog End Example.c
  
  Run function that blinks a light with another cog continuously.
  Shut down that other cog from main routine.

  http://learn.parallax.com/multicore-approaches/stopping-cores
*/

#include "simpletools.h"                       // Library include

void blink();                                  // Forward declaration

int main()                                     // Main function
{
  int *cog = cog_run(blink, 128);              // Run blink in other cog
  pause(3000);                                 // Wait while other cog blinks LED
  cog_end(cog);                                        
}

void blink()                                    // Blink function for other cog
{
  while(1)                                      // Endless loop for other cog
  {
    high(26);                                   // P26 LED on
    pause(100);                                 // ...for 0.1 seconds
    low(26);                                    // P26 LED off
    pause(100);                                 // ...for 0.1 seconds
  }
}

