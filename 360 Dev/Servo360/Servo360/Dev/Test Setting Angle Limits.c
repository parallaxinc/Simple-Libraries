/*
  With setAngleLimits in effect, the actual angles are: 
    0, -85,  -90, 40, 45, 0
  ...even though the program requests: 
    0, -85, -180, 40, 90, 0
*/

#include "simpletools.h"
#include "servo360.h"

int main()
{
  servo360_connect(12, 14);
  
  servo360_setAngleLimits(12, 45, -90);
  pause(1000);
  
  servo360_angle(12, 0);
  pause(1000);
  servo360_angle(12, -85); 
  pause(1000);
  servo360_angle(12, -180);
  pause(1000);
  servo360_angle(12, 40);
  pause(1000);
  servo360_angle(12, 90);
  pause(1000);
  servo360_angle(12, 0);
  pause(1000);
}
