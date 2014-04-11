/*
  Lock Example.c
  
  How to modify your code for a precisely timed process:
   - Run with terminal as-is and note system clock ticks per cycle.
   - Comment puase statements in blink function.
   - Un-comment wiatcnt statements in blink function.
   - Run again, and note difference in system clock ticks per cycle.

  http://learn.parallax.com/propeller-c-multicore-approaches/timing-example
*/

#include "simpletools.h"                      // Library include

void blink();                                 // Forward declaration
int *cog;                                     // For storing process ID
volatile int dt;                              // Declare dt for both cogs 
volatile int tNow = 0;                        // For storing current CNT

int main()                                    // Main function
{
  dt = 500;                                   // Set value of t to 100
  cog = cog_run(&blink, 10);                  // Run blink in other cog

  while(tNow == 0);                           // Wait for blink to set tNow
  int tNowOld = tNow;                         // Record that time
  while(1)                                    // Main loop
  {
    while(tNow == tNowOld);                   // Wait for blink to change tNow
    print("ticks = %d\n", tNow - tNowOld);    // Print tLow - tNowOld
    tNowOld = tNow;                           // New tNowOld for next while rep
  }
}

void blink()                                  // Function for other cog
{
  int t = CNT;                                // Mark the time
  while(1)                                    // Endless loop
  {
    high(26);                                 // LED on
    pause(dt);                                // Not precise
    // waitcnt(t += dt*ms);                   // Precise
    low(26);                                  // LED off
    pause(dt);                                // Not precise
    // waitcnt(t += dt*ms);                   // Precise
    tNow = CNT;
  }
}