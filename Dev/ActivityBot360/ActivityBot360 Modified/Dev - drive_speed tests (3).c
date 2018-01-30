#include "simpletools.h"
#include "abdrive360.h"

int main()                   
{
  drive_speed(0, 0);
  drive_setRampStep(1);
  pause(50);

  drive_speed(64, 64);
  pause(2000);
  drive_speed(0, 0);
  pause(2000);
  drive_speed(-64, -64);
  pause(2000);
  drive_speed(0, 0);
  pause(2000);
  while(1);
}