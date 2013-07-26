/*
  Count Transitions.c
  
  Flash P26 at 10 Hz for 10 seconds.  After 1 s, count transitions for 1 s
  and report the count.
  
  http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  square_wave(26, 0, 10);                     // P26, ch0, 10 Hz.
  pause(1000);                                // Pause 1 second

  int cycles = count(26, 1000);               // Count for 1 second
  print("cycles = %d\n", cycles);             // Report on/off cycles

  // Negative pin clears signal and lets go of I/O pin.
  square_wave(-26, 0, 0);                     
}

