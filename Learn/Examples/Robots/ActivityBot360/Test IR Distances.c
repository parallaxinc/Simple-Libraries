/*
  IR Test Distances.c

  Test distance detection with infrared detectors.

  http://learn.parallax.com/activitybot/ir-test-distances
*/

#include "simpletools.h"                        // Include simpletools
#include "abdrive360.h"
#include "abvolts.h"

int irLeft, irRight;                            // Global variables

int main()                                      // Main function
{
  while(1)                                      // Main loop
  {
    irLeft = 0;                                 // Detect variables to 0
    irRight = 0;
    
    // Test if an object is detected with 9 increasing levels of IR LED
    // brightness.  Keep track of the number of times an object is NOT
    // detected.  That's its distance value.  
    
    for(int da = 448; da >= 0; da -= 64)        // Sweep da pins 
    {
      da_out(0, da);                            // Set IR LED cathode volts
      da_out(1, da);
      freqout(11, 1, 38000);                    // Left IR LED light
      irLeft += input(10);                      // No detect?  Add 1 to irLeft
      freqout(1, 1, 38000);                     // Repeat for right detector
      irRight += input(2);
    }   

    print("%c irLeft = %d, irRight = %d     ",  // Display detector states
           HOME,       irLeft,       irRight);
    pause(100);                                 // Pause before repeating
  }
}

