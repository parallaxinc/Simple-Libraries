/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot/go-certain-distances
*/


#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  /*
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  */

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