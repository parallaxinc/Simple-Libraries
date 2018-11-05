/*
  IR Test Distances.c

  Test distance detection with infrared detectors.

  http://learn.parallax.com/activitybot/ir-test-distances
*/

#include "simpletools.h"                        // Include simpletools
#include "abdrive360.h"

int irLeft, irRight;                            // Global variables

int main()                                      // Main function
{
  pwm_start(255);

  low(26);                                      // D/A0 & D/A1 to 0 V
  low(27);

  while(1)                                      // Main loop
  {
    irLeft = 0;                                 // Detect variables to 0
    irRight = 0;
    
    for(int da = 189; da >= 0; da -= 27)        // Sweep da pins 
    {
      pwm_set(26, 0, da); 
      pwm_set(27, 1, da);
      freqout(11, 1, 38000);                    // Left IR LED light
      irLeft += input(10);                      // Check left IR detector
      freqout(1, 1, 38000);                     // Repeat for right detector
      irRight += input(2);
    }   

    print("%c irLeft = %d, irRight = %d     ",  // Display detector states
           HOME,       irLeft,       irRight);
    pause(100);                                 // Pause before repeating
  }
}

