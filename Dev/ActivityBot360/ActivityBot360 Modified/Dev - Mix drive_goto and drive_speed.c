//#define _servo360_monitor_

#include "simpletools.h"
#include "abdrive360.h"

int main()
{
  //
  #ifdef _servo360_monitor_
    //drive_speed(0, 0);
    servo360_monitor_start();
    //suppressFbDisplay = 0;
  #endif 
  //

  drive_speed(64, 64); // goes forward
  pause(2000); // wait
  drive_speed(0, 0); // drive stop
  pause(2000); // wait
  drive_goto(30, 30); // should drive forward but robot goes backwards bug here!
  drive_speed(0, 0);
}





