/*
  Follow with Ping.c

  Maintain a constant distance between ActivityBot and object.

  http://learn.parallax.com/activitybot/follow-objects-ultrasound
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header  

int distance, setPoint, errorVal, kp, speed;  // Navigation variables

int main()                                    // main function
{
  setPoint = 32;                              // Desired cm distance
  kp = -10;                                   // Proportional control

  drive_setRampStep(6);                       // 7 ticks/sec / 20 ms

  while(1)                                    // main loop
  {
    distance = ping_cm(8);                    // Measure distance
    errorVal = setPoint - distance;           // Calculate error
    speed = kp * errorVal;                    // Calculate correction speed

    if(speed > 128) speed = 128;              // Limit top speed
    if(speed < -128) speed = -128;

    drive_rampStep(speed, speed);             // Use result for following
  }
}

