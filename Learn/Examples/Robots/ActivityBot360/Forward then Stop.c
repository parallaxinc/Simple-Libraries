/* 
  Forward Stop Face Right.c

  https://learn.parallax.com/ab360
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_speed(64, 64);
  pause(4000);
  drive_speed(0, 0);
}