/* 
  Test for Trim.c

  Test and adjust trim for servos and encoders

  http://learn.parallax.com/activitybot/test-and-tune-your-activitybot
*/

#include "simpletools.h"
#include "abdrive.h"

int main()                   
{
  drive_trimSet(0, 0, 0);
  drive_speed(32, 32);
  pause(8000);
  drive_speed(0, 0);
}


