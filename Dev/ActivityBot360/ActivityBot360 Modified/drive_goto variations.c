/* 
  drive_goto variations.c
*/


#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_goto(192, 192);
  pause(1000);
  drive_goto(-28, 28);
  pause(1000);
  drive_goto(28 * 2, -28 * 2);
  pause(1000);
  drive_goto(-28, 28);
  pause(1000);
  drive_goto(-192, -192);
  pause(1000);
  
  drive_goto(192, 128);
  pause(1000);
  drive_goto(-192, -128);
  pause(1000);
  drive_goto(128, 192);
  pause(1000);
  drive_goto(-128, -192);
  pause(1000);
}