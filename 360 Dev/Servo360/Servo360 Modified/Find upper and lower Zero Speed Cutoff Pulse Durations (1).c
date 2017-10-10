/*
  Find upper and lower Zero Speed Cutoff Pulse Durations.c
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  
  // Left servo counterclockwise

  servo360_connect(12, 14);
  servo360_feedback(12, 0);
  
  int n, y1, y2, x1, x2; 
  int mVccw, mVcw, bVccw, bVcw;
  int increases = 0, decreases = 0;
  int angle = servo360_getAngle(12);
  int anglep = angle;
  int diffCount = 0;
  
  servo360_set(12, 1500+240);
  pause(2000);
  x1 = servo360_getAngle12Bit(12);
  print("x1 = %d\r", x1);
  pause(1000);
  x1 = servo360_getAngle12Bit(12) - x1;
  print("x1 = %d\r", x1);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(12, 1500);
  
  pause(2000);

  angle = servo360_getAngle(12);
  anglep = angle;

  for(n = 0; n < 60; n++)
  {
    servo360_set(12, 1500 + n);
    angle = servo360_getAngle(12);
    print("angle = %d\r", angle);
    if(angle != anglep) increases++;
    if(increases > 3) break;
    pause(20);
  }  
  
  bVccw = (n - 4) * 10 * 2 / 3;
  print("bVccw = %d\r", bVccw); 
  
  servo360_set(12, 1500);

  mVccw = 1000 * (2200 - 266) / x1;

  print("mVccw = %d\r", mVccw); 
  
  
  // Left servo clockwise


  servo360_set(12, 1500-240);
  pause(2000);
  x1 = servo360_getAngle12Bit(12);
  print("x1 = %d\r", x1);
  pause(1000);
  x1 = abs(servo360_getAngle12Bit(12) - x1);
  print("x1 = %d\r", x1);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(12, 1500);
  
  pause(2000);

  angle = servo360_getAngle(12);
  anglep = angle;

  for(n = 0; n > -60; n--)
  {
    servo360_set(12, 1500 + n);
    angle = servo360_getAngle(12);
    print("angle = %d\r", angle);
    if(angle != anglep) decreases++;
    if(decreases > 3) break;
    pause(20);
  }  
  
  bVcw = abs((n + 4) * 10 * 2 / 3);
  print("bVcw = %d\r", bVcw); 
  
  servo360_set(12, 1500);

  mVcw = 1000 * (2200 - 266) / x1;

  print("mVccw = %d\r", mVcw); 

  while(1);


}