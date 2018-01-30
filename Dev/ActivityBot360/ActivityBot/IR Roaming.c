/*
  IR Roaming.c

  Use IR LED and IR receiver pairs as object detectors for robot roaming.

  http://learn.parallax.com/activitybot/roaming-infrared-flashlights
*/

#include "simpletools.h"                        // Library includes
#include "abdrive.h"

int irLeft, irRight;                            // IR variables

int main()                                      // Main function
{
  low(26);                                      // D/A0 & D/A1 to 0 V
  low(27);

  drive_setRampStep(12);                        // Max step 12 ticks/s every 20 ms

  while(1)
  {
    freqout(11, 1, 38000);                      // Check left & right objects
    irLeft = input(10);

    freqout(1, 1, 38000);
    irRight = input(2);

    if(irRight == 1 && irLeft == 1)             // No obstacles?
      drive_rampStep(128, 128);                 // ...full speed ahead
    else if(irLeft == 0 && irRight == 0)        // Left & right obstacles?
      drive_rampStep(-128, -128);               // ...full speed reverse
    else if(irRight == 0)                       // Just right obstacle?
      drive_rampStep(-128, 128);                // ...rotate left
    else if(irLeft == 0)                        // Just left obstacle?
      drive_rampStep(128, -128);                // ...rotate right
  }
}
