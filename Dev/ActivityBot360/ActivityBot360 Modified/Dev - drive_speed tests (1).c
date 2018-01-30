#include "simpletools.h"
#include "abdrive360.h"

int main()                   
{
  drive_speed(0, 0);
  pause(100);
  //
  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 
  // 
  
  pause(1000);

  drive_setRampStep(4);

  drive_speed(64, 64);
  pause(2000);
  drive_speed(0, 0);
  pause(2000);
  drive_speed(-64, -64);
  pause(2000);
  drive_speed(0, 0);
  pause(2000);
  drive_setRampStep(8);
  drive_speed(128, 128);
  pause(1000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-128, -128);
  pause(1000);
  drive_speed(0, 0);
  pause(1000);
  suppressFbDisplay = 1;
  while(1);
  drive_speed(64, 64);
  pause(2000);
  drive_speed(-64, -64);
  pause(1000);
  drive_speed(0, 0);
  pause(1000);
}