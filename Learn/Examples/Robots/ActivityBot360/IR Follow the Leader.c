/*
  IR Follow the Leader.c

  Follow another ActivityBot 360, your hand and other targets.

  http://learn.parallax.com/activitybot/ir-follow-the-leader
*/

#include "simpletools.h"                        // Include simpletools
#include "abdrive360.h"
#include "abvolts.h"

int irLeft, irRight;                            // Global variables
int errorLeft, errorRight;
int driveLeft, driveRight;
int setPoint = 4; 
int kp = -12;

int main()                                      // Main function
{
  while(1)                                      // Main loop
  {
    irLeft = 0;                                 // Detect variables to 0
    irRight = 0;
    
    for(int da = 112; da >= 0; da -= 16)        // Sweep da pins 
    {
      da_out(0, da);                            // Set IR LED cathode volts
      da_out(1, da);
      freqout(11, 1, 38000);                    // Left IR LED light
      irLeft += input(10);                      // No detect?  Add 1 to irLeft
      freqout(1, 1, 38000);                     // Repeat for right detector
      irRight += input(2);
    }   

    errorLeft = setPoint - irLeft;              // Error = want - measured
    errorRight = setPoint - irRight;
    
    driveLeft = kp * errorLeft;                 // Output = k * error
    driveRight = kp * errorRight;
    
    drive_speed(driveLeft, driveRight);         // Set outputs
  }
}

