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
  
  int n, x, angle, angleP; 
  int mVccwL, mVcwL, bVccwL, bVcwL;
  int mVccwR, mVcwR, bVccwR, bVcwR;
  int increases = 0, decreases = 0, diffCount = 0;
  
  servo360_set(12, 1500+240);
  pause(2000);
  x = servo360_getAngle12Bit(12);
  print("x = %d\r", x);
  pause(1000);
  x = servo360_getAngle12Bit(12) - x;
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(12, 1500);
  
  pause(2000);

  angle = servo360_getAngle(12);
  angleP = angle;

  for(n = 0; n < 60; n++)
  {
    servo360_set(12, 1500 + n);
    angle = servo360_getAngle(12);
    print("angle = %d\r", angle);
    if(angle != angleP) increases++;
    if(increases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVccwL = (n - 4) * 10 * 2 / 3;
  print("bVccwL = %d\r", bVccwL); 
  
  servo360_set(12, 1500);

  mVccwL = 1000 * (2200 - bVccwL) / x;

  print("mVccwL = %d\r", mVccwL); 
  
  
  // Left servo clockwise


  servo360_set(12, 1500-240);
  pause(2000);
  x = servo360_getAngle12Bit(12);
  print("x = %d\r", x);
  pause(1000);
  x = abs(servo360_getAngle12Bit(12) - x);
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(12, 1500);
  
  pause(2000);

  angle = servo360_getAngle(12);
  angleP = angle;

  for(n = 0; n > -60; n--)
  {
    servo360_set(12, 1500 + n);
    angle = servo360_getAngle(12);
    print("angle = %d\r", angle);
    if(angle != angleP) decreases++;
    if(decreases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVcwL = abs((n + 4) * 10 * 2 / 3);
  print("bVcwL = %d\r", bVcwL); 
  
  servo360_set(12, 1500);

  mVcwL = 1000 * (2200 - bVcwL) / x;

  print("mVccwL = %d\r", mVcwL); 

  
  // Right servo counterclockwise

  servo360_connect(13, 15);
  servo360_feedback(13, 0);
  
  servo360_set(13, 1500+240);
  pause(2000);
  x = servo360_getAngle12Bit(13);
  print("x = %d\r", x);
  pause(1000);
  x = servo360_getAngle12Bit(13) - x;
  print("x = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(13, 1500);
  
  pause(2000);

  angle = servo360_getAngle(13);
  angleP = angle;
  increases = 0;
  
  for(n = 0; n < 60; n++)
  {
    servo360_set(13, 1500 + n);
    angle = servo360_getAngle(13);
    print("angle = %d\r", angle);
    if(angle != angleP) increases++;
    if(increases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVccwR = (n - 4) * 10 * 2 / 3;
  print("bVccwR = %d\r", bVccwR); 
  
  servo360_set(13, 1500);

  mVccwR = 1000 * (2200 - bVccwR) / x;

  print("mVccwR = %d\r", mVccwR); 
  
  
  // Right servo clockwise


  servo360_set(13, 1500-240);
  pause(2000);
  x = servo360_getAngle12Bit(13);
  print("x = %d\r", x);
  pause(1000);
  x = abs(servo360_getAngle12Bit(13) - x);
  print("x1 = %d\r", x);
  //x1 &= 0xFFF;
  //print("x1 = %d\r", x1);

  servo360_set(13, 1500);
  
  pause(2000);

  angle = servo360_getAngle(13);
  angleP = angle;
  decreases = 0;

  for(n = 0; n > -60; n--)
  {
    servo360_set(13, 1500 + n);
    angle = servo360_getAngle(13);
    print("angle = %d\r", angle);
    if(angle != angleP) decreases++;
    if(decreases > 3) break;
    pause(20);
    angleP = angle;
  }  
  
  bVcwR = abs((n + 4) * 10 * 2 / 3);
  print("bVcwR = %d\r", bVcwR); 
  
  servo360_set(13, 1500);

  mVcwR = 1000 * (2200 - bVcwR) / x;

  print("mVcwR = %d\r", mVcwR); 

  print("\r=== Summary ===\r", mVcwR); 
  print("mVccw = %d\r", mVccwL); 
  print("bVccwL = %d\r", bVccwL); 
  print("mVcwL = %d\r", mVcwL); 
  print("bVcwL = %d\r", bVcwL); 
  print("mVccwR = %d\r", mVccwR); 
  print("bVccwR = %d\r", bVccwR); 
  print("mVcwR = %d\r", mVcwR); 
  print("bVcwR = %d\r", bVcwR); 

}