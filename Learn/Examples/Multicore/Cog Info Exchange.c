/*
  Cog Info Exchange.c
 
  Example of two cogs exchanging information with a volatile global variable.
  The main function in cog 0 changes the value; and it affects the blink function's
  rate running in cog 1.

  http://learn.parallax.com/multicore-approaches/cores-sharing-data
*/

#include "simpletools.h"                      // Library include

void blink();                                 // Forward declaration
int *cog;                                     // For storing process ID
volatile int dt;                              // Declare dt for both cogs

int main()                                    // Main function
{
  dt = 100;                                   // Set value of dt to 100
  cog = cog_run(blink, 128);                  // Run blink in other cog
  pause(2000);                                // Let run for 2 s

  dt = 50;                                    // Update value of dt
  pause(2000);                                // New rate for 2 s
  cog_end(cog);                               // Stop the cog
}

void blink()                                  // Function for other cog
{
  while(1)                                    // Endless loop
  {
    high(26);                                 // LED on
    pause(dt);                                // ...for dt ms
    low(26);                                  // LED off
    pause(dt);                                // ...for dt ms
  }
}