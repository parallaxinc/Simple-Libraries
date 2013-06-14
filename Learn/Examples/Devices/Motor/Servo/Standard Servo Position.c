/*
  Standard Servo Position.c
  
  Moves servo to 0, 90 and 180 degrees.  Holds each position for 2 s.
  Connect servo to P16 port on Propeller ActivityBoard.
  
  http://learn.parallax.com/propeller-c-simple-devices/standard-servo-position
*/

#include "simpletools.h"                      // Include simpletools header
#include "servo.h"                            // Include servo header

int main()                                    // Main function
{
  servo_angle(16, 0);                         // P16 servo to 0 degrees
  pause(3000);                                // ...for 3 seconds
  servo_angle(16, 900);                       // P16 servo to 90 degrees
  pause(3000);                                // ...for 3 seconds
  servo_angle(16, 1800);                      // P16 servo to 180 degrees
  pause(3000);                                // ...for 3 seconds
  servo_stop();                               // Stop servo process
}

