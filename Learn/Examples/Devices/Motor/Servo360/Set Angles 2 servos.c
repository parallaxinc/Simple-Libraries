/*
  Set Angles.c
  
  Turns to and holds positions.  
  Behaves like a standard RC servo when it reaches a given angle.
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
  pause(1000);
  
  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(1000);

  servo360_angle(12, 45);
  servo360_angle(13, -45);
  pause(1500);
   
  servo360_angle(12, 360 + 45);
  servo360_angle(13, -360 -45);
  pause(2500);

  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(1000);
}
