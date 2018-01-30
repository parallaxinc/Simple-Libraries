/*
  In practice, your 
  application would most likely check if the result of servo360_getAngle
  is approaching the thresholds, and then subtract some negative number 
  of turns.  This test verifies turning back the turns clock.  You may
  see some rounding errors, but that will not affect angle, speed, or 
  goto navigation.  The goal here is just to move the turns way back 
  to prevent rolover in certain variables.
*/  

#include "simpletools.h"
#include "abdrive360.h"

int main()
{
  drive_speed(0, 0);
  
  int turns = servo360_getTurns(12);
  print("turns = %d\r", turns);

  servo360_setTurns(12, 500000);
  pause(100);
  
  drive_speed(32, 32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  
  turns = servo360_getTurns(12);
  print("turns = %d\r", turns);
  servo360_setTurns(12, -turns);
  pause(100);
  
  drive_speed(-32, -32);
  pause(2000);
  drive_speed(0, 0);

  turns = servo360_getTurns(12);
  print("turns = %d\r", turns);
  pause(500);
}  

