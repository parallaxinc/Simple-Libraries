/*
  Dev - Test set and get functions.c
*/

#include "simpletools.h"
#include "servo360.h"

static int upperLimit, lowerLimit, angle, speed, op, 
           units, acceleration, step, value, turns;

int main()
{
  print("connect 12, 14\r");
  servo360_connect(12, 14);
  
  print("set angle limits 12, 45, -90\r");
  servo360_setAngleLimits(12, 45, -90);
  servo360_getAngleLimits(12, &upperLimit, &lowerLimit);
  print("upperLimit = %d, lowerLimit = %d\r\r",
         upperLimit,      lowerLimit);

  print("set angle limits 12, S360_A_MAX, -S360_A_MAX\r");
  servo360_setAngleLimits(12, 45, -90);
  servo360_getAngleLimits(12, &upperLimit, &lowerLimit);
  print("upperLimit = %d, lowerLimit = %d\r\r",
         upperLimit,      lowerLimit);

  print("set angle to 0\r");
  servo360_angle(12, 0);
  angle = servo360_getAngle(12);  
  print("angle = %d\r", angle);
  print("set angle to 180\r");
  servo360_angle(12, 180);
  angle = servo360_getAngle(12); 
  for(int n = 0; n < 5; n++)
  { 
    print("angle = %d\r", angle);
    pause(100);
  }    

  print("set speed to 90\r");
  servo360_speed(12, 90);
  for(int n = 0; n < 5; n++)
  { 
    angle = servo360_getAngle(12);  
    speed = servo360_getSpeed(12);  
    print("angle = %d, speed = %d\r", angle, speed);
    pause(100);
  }    
  print("speed to -180\r");
  servo360_speed(12, -180);
  for(int n = 0; n < 5; n++)
  { 
    angle = servo360_getAngle(12);  
    speed = servo360_getSpeed(12);  
    print("angle = %d, speed = %d\r", angle, speed);
    pause(100);
  }    
  print("set speed to 0\r");
  servo360_speed(12, 0);
  for(int n = 0; n < 5; n++)
  { 
    angle = servo360_getAngle(12);  
    speed = servo360_getSpeed(12);  
    print("angle = %d, speed = %d\r", angle, speed);
    pause(100);
  }    

  
  print("goto 1080\r");
  servo360_goto(12, 1080);
  pause(50);
  int n = 0;
  do
  { 
    op = servo360_getCsop(12);
    angle = servo360_getAngle(12);  
    speed = servo360_getSpeed(12);  
    print("op = %d, angle = %d, speed = %d\r", op, angle, speed);
    pause(100);
  }
  while(n++ < 20 && op != 1);
  for(int n = 0; n < 5; n++)
  { 
    op = servo360_getCsop(12);
    angle = servo360_getAngle(12);  
    speed = servo360_getSpeed(12);  
    print("op = %d, angle = %d, speed = %d\r", op, angle, speed);
    pause(100);
  }    
  
  
  print("units full circle to 64\r");
  servo360_setUnitsFullCircle(12, 64);
  units = servo360_getUnitsFullCircle(12);  
  print("units full circle = %d\r\r", units);


  print("max speed to 96\r");
  servo360_setMaxSpeed(12, 96);
  speed = servo360_getMaxSpeed(12);  
  print("max speed = %d\r\r", speed);


  print("acceleration to 300\r");
  servo360_setAcceleration(12, 300);
  acceleration = servo360_getAcceleration(12);  
  print("acceleration = %d\r\r", acceleration);

  // Maybe add a navigation test here
  
  print("ramp step to 8\r");
  servo360_setRampStep(12, 8);
  step = servo360_getRampStep(12);
  print("ramp step = %d\r\r", step);


  print("control system settings\r");
  value = servo360_getControlSys(12, S360_KPV);
  print("KpV = %d\r", value);
  value = servo360_getControlSys(12, S360_KIV);
  print("KiV = %d\r", value);
  value = servo360_getControlSys(12, S360_KDV);
  print("KdV = %d\r", value);
  value = servo360_getControlSys(12, S360_IV_MAX);
  print("I max V = %d\r", value);
  value = servo360_getControlSys(12, S360_KPA);
  print("KpA = %d\r", value);
  value = servo360_getControlSys(12, S360_KIA);
  print("KiA = %d\r", value);
  value = servo360_getControlSys(12, S360_KDA);
  print("KdA = %d\r", value);
  value = servo360_getControlSys(12, S360_IV_MAX);
  print("I max A = %d\r\r", value);


  print("Add 64 to turns\r");
  servo360_setTurns(12, 64);
  turns = servo360_getTurns(12);  
  print("turns = %d\r", turns);
  print("subtract 64 from turns\r");
  servo360_setTurns(12, -turns);
  turns = servo360_getTurns(12);  
  print("turns = %d\r\r", turns);


  print("Restore default units\r");
  servo360_setUnitsFullCircle(12, 360);
  servo360_setMaxSpeed(12, 720);
  servo360_setAcceleration(12, 2000);

  print("Run Full speed, will stop in 2 s...\r");
  servo360_speed(12, 540);
  pause(2000);
  servo360_stop(12);
  print("stop call!\r\r");
  pause(1500);


  print("set angle to -96\r");
  servo360_angle(12, -96);
  pause(5000);
  angle = servo360_getAngle(12);  
  print("angle = %d\r", angle);
  angle = servo360_getAngleFixedOrigin(12);  
  print("angle from origin = %d\r", angle);
  angle = servo360_getAngle12Bit(12);  
  print("12 bit angle = %d\r", angle);
  angle = servo360_getAngleCalc(12);  
  print("angle = %d\r\r", angle);
  pause(1000);


  print("Run without feedback\r");
  servo360_feedback(12, 0);
  print("Set 1540 us pulses\r");
  servo360_set(12, 1540);
  pause(2000);
  print("Set 1460 us pulses\r");
  servo360_set(12, 1460);
  pause(2000);
  print("Set 1500 us pulses\r\r");
  servo360_set(12, 1500);


  print("Run with feedback\r");
  servo360_feedback(12, 1);
  pause(100);
  print("speed 360\r");
  servo360_speed(12, 360);
  pause(2000);
  print("speed -360\r");
  servo360_speed(12, -360);
  pause(2000);
  print("speed 0\r\r");
  servo360_speed(12, 0);
  pause(2000);
  
  
  print("All done!");  
}
