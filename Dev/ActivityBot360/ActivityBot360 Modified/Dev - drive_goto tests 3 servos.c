/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot/go-certain-distances
*/


#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  /*
  #ifdef _servo360_monitor_
    servo360_monitor_start();
    suppressFbDisplay = 0;
  #endif 
  */

  drive_goto(192, 192);
  servo360_connect(16, 6);
  servo360_speed(16, 90);
  drive_goto(-28, 28);
  drive_goto(28 * 2, -28 * 2);
  drive_goto(-28, 28);
  drive_goto(-192, -192);
  servo360_speed(16, -90);
  
  drive_goto(192, 128);
  drive_goto(-192, -128);
  drive_goto(128, 192);
  drive_goto(-128, -192);
  servo360_speed(16, 0);
}