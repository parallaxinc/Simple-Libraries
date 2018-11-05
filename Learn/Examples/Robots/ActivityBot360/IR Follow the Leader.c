/*
  IR Follow the Leader.c

  Follow another ActivityBot 360, your hand and other targets.

  http://learn.parallax.com/activitybot/ir-follow-the-leader
*/

#include "simpletools.h"                        // Include simpletools
#include "abdrive360.h"

int irLeft, irRight;                            // Global variables
int errorLeft, errorRight;
int driveLeft, driveRight;
int setPoint = 4; 
int kp = -12;

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

    errorLeft = setPoint - irLeft;
    errorRight = setPoint - irRight;
    
    driveLeft = kp * errorLeft;
    driveRight = kp * errorRight;
    
    drive_speed(driveLeft, driveRight);
  }
}

