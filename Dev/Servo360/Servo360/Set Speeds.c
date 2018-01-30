/*
  Set Speeds.c
  
  Turn at speeds for certain amounts of time. 
  
  Note that a change in direction involves deceleration and then acceleration, so
  the wheels will not return to their original angles in the same amount of time. 
  
  By default, speeds are in degrees (360ths of a revolution) per second.
*/

#include "simpletools.h"
#include "servo360.h"

int main()
{
  // Connect is required before control.  The first argument is the I/O pin 
  // connected to the white control line, and the second is the I/O pin connected
  // to the yellow feedback line.
  servo360_connect(12, 14);
  servo360_connect(13, 15);

  //Optionally set acceleration in degrees/s^2
  servo360_setAcceleration(12, 1080);
  servo360_setAcceleration(13, 1080);

  // Start with 15 RPM (1/4 RPs)
  servo360_speed(12, -90);
  servo360_speed(13, 90);
  pause(2000);
   
  // Reverse direction
  servo360_speed(12, 90);
  servo360_speed(13, -90);
  pause(2000);
   
  // Start with 120 RPM (2 RPs)
  servo360_speed(12, -720);
  servo360_speed(13, 720);
  pause(2000);
   
  // Reverse direction
  servo360_speed(12, 720);
  servo360_speed(13, -720);
  pause(4000);
   
  // Stop
  servo360_speed(12, 0);
  servo360_speed(13, 0);
  pause(1000);
  
  // Optionally hold the curent position with more force than 
  // the speed control resting control system applies by switching
  // to angular control.
  
  int angleLeft = servo360_getAngle(12);
  int angleRight = servo360_getAngle(13);
  
  servo360_angle(12, angleLeft);
  servo360_angle(13, angleRight);
}
