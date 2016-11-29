/*
  Navigate by Light.c

  http://learn.parallax.com/activitybot/roaming-light-sensors
*/

#include "simpletools.h"
#include "abdrive.h"

int lightLeft, lightRight, ndiff;
int speedLeft, speedRight;

int main()                    
{
  while(1)
  {
    high(9);
    pause(1);
    lightLeft = rc_time(9, 1);
    
    high(5);
    pause(1);
    lightRight = rc_time(5, 1);

    ndiff = 200 * lightRight / (lightRight + lightLeft) - 100;

    speedLeft = 100;
    speedRight = 100;
    if(ndiff >= 0) speedLeft -= (ndiff * 4);
    else speedRight += (ndiff * 4);

    drive_speed(speedLeft, speedRight);
  }
}
