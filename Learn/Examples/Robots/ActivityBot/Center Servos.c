/*
  Center Servos.c
  
  This program can be run if ActivityBot Display Calibration shows that one of 
  the servos has a zero Encoder Ticks/Second that's more than +/- 30 from 
  the zero in the Servo Drive column. 
  
  This program sends a 1500 us pulses to the left and right servos. With the 
  PWR switch set to 2, adjust the servos to stay still in in response to these 
  signals by using a Philips screwdriver to turn the potentiometer adjusting 
  screw under the hole in the case adjacent to the servo’s cable.

  IMPORTANT: After both servos have been adjusted, repeat the procedure in 
             http://learn.parallax.com/activitybot/calibrate-your-activitybot
*/

#include "simpletools.h"
#include "servo.h"

int main() 
{
  servo_set(13, 1500);
  servo_set(12, 1500);
  
  print("Use a screwdriver to adjust ActivityBot's servos\n");
  print("to stop with PWR set to 2.\n\n");
  print("Then, make sure to follow the procedure on\n");
  print("http://learn.parallax.com/activitybot/calibrate-your-activitybot.\n");
}


