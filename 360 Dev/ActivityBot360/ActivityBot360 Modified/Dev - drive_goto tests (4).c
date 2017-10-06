#define _servo360_monitor_

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  
  //
  #ifdef _servo360_monitor_
    //drive_speed(0, 0);
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 
  //
  
  suppressFbDisplay = 0;
  drive_speed(0, 0);
  servo360_angle(12, 0);
  suppressFbDisplay = 0;
  servo360_angle(13, 0);
  suppressFbDisplay = 0;
  pause(100);
  //suppressFbDisplay = 0;
  //servo360_angle(12, 0);
  //suppressFbDisplay = 0;
  //servo360_angle(13, 0);
  suppressFbDisplay = 0;
  
  
  
  
  
  pause(1500);

  suppressFbDisplay = 0;
  drive_goto(2, 2);
  suppressFbDisplay = 0;
  pause(1500);
  
  drive_goto(-2, -2);
  pause(1500);
  
  drive_goto(-2, -2);
  pause(1500);
  
  drive_goto(2, 2);
  pause(1500);
  
  drive_goto(2, 2);
  pause(1500);
  
  drive_goto(-2, -2);
  pause(1500);
  
  #ifdef _servo360_monitor_
  suppressFbDisplay = 1;
  #endif
  while(1);

  drive_goto(64, 64);
  pause(1500);
  drive_goto(64, 64);
  pause(1500);
  drive_goto(64, 64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);
  drive_goto(-64, -64);
  pause(1500);


  while(1);








  drive_goto(192, 192);
  pause(1500);
  drive_goto(-28, 28);
  pause(1500);
  drive_goto(28 * 2, -28 * 2);
  pause(1500);
  drive_goto(-28, 28);
  pause(1500);
  drive_goto(-192, -192);
  pause(1500);
  
  drive_goto(192, 128);
  pause(1500);
  drive_goto(-192, -128);
  pause(1500);
  drive_goto(128, 192);
  pause(1500);
  drive_goto(-128, -192);
  pause(1500);
}