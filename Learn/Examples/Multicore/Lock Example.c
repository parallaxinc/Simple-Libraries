/*
  Lock Example.c
  
  Main and blink functions share a lock.  The blink function prevents main
  from changing the value of t, except at the start of its low cycle.

  http://learn.parallax.com/propeller-c-multicore_approaches/lock-example
*/

#include "simpletools.h"                      // Library include

void blink();                                 // Forward declaration
int *cog;                                     // For storing process ID
volatile int dt;                              // Declare t for both cogs
volatile int lockID;                          // For storing lock ID

int main()                                    // Main function
{
  dt = 100;                                   // Set value of t to 100
  lockID = locknew();                         // Check out a lock
  cog = cog_run(&blink, 64);                  // Run blink in other cog
  pause(1883);                                // Let run for 2 s

  while(lockset(lockID));                     // Wait for blink to release lock 
  dt = 50;                                    // Update value of t
  lockclr(lockID);                            // Release lock for blink
  
  pause(2000);                                // New rate for 2 s
  cog_end(cog);                               // Stop the cog
}

void blink()                                  // Function for other cog
{
  while(1)                                    // Endless loop
  {
    while(lockset(lockID));                   // Wait for lock
    high(26);                                 // LED on
    pause(dt);                                // ...for t ms
    lockclr(lockID);                          // Release lock
    low(26);                                  // LED off
    pause(dt);                                 // ...for t ms
  }
}