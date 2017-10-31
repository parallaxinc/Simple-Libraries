/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot/go-certain-distances
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_speed(64, 64);
  pause(4000);
  drive_speed(0, 0);
}