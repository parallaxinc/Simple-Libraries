/*
  Set Volts.c
  
  Set voltages at D/A 0 with P26 and at D/A 1 with P27.
  V(D/A) = daVal * 3.3 V / 256.

  Examples:
    78 * 3.3 V / 256 -> 1 V
    233 * 3.3 V / 256 -> 3 V.
    
  For more options and channels, use: 
    Learn\Simple Libraries\Convert\libdacctr   
  
  http://learn.parallax.com/propeller-c-simple-circuits/set-voltage-output
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  dac_ctr(26, 0, 233);                        // 3 V to D/A 0
  dac_ctr(27, 1, 78);                         // 1 V to D/A 1
  pause(2000);                                // Pause 2 seconds
  dac_ctr(26, 0, 78);                         // 1 V to D/A 0
  dac_ctr(27, 1, 233);                        // 3 V to D/A 1
  pause(2000);                                // Pause 2 seconds
  
  int i = 0;                                  // Index variable
  while(1)                                    // Repeat indefinitely
  {
    dac_ctr(26, 0, i);                        // D/A 0 V = 3.3 * i/256
    dac_ctr(27, 1, 256-i);                    // D/A 1 V = 3.3 * (256-i)/256
    pause(4);                                 // Pause 4 ms
    if(++i == 256) i = 0;                     // Increment i in 0..255 range
  }
}

