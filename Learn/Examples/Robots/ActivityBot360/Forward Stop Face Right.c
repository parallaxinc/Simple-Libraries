/* 
  Forward Stop Face Right.c

  https://learn.parallax.com/ab360
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_goto(256, 256);
  pause(200);
  drive_goto(26, -25);
}