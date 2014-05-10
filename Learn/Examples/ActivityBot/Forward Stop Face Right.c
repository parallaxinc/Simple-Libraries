/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot
*/

#include "simpletools.h"
#include "abdrive.h"

int main()                    
{
  drive_goto(256, 256);
  pause(200);
  drive_goto(26, -25);
}