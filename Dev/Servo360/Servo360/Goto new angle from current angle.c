/*
  Goto new angle from current angle.c
  
  Turn to a new position, relative to the current position. 
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
  
  // Optionally redefine what a degree is.  
  // This changes a degree from the 360 degree default to 
  // a new value of 256.  
  servo360_setUnitsFullCircle(12, 256);
  servo360_setUnitsFullCircle(13, 256);

  // Optionally set acceleration in degree units/s^2
  servo360_setAcceleration(12, 128);
  servo360_setAcceleration(13, 128);

  // Optionally restrict the cruising speed in degrees/s
  servo360_setMaxSpeed(12, 392);
  servo360_setMaxSpeed(13, 392);
  
  pause(1000);
  
  servo360_speed(12, 0);
  servo360_speed(13, 0);
  
  pause(1000);
  
  // Go for 2 turns counterclockwise
  servo360_goto(12, 512);
  servo360_goto(13, -512);
  
  pause(4000);

  // Go for 1 turn clockwise
  servo360_goto(12, -256);
  servo360_goto(13, 256);
}
