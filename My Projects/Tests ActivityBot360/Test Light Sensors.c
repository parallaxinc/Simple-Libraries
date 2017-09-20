/*
  Test Light Sensors.c

  http://learn.parallax.com/activitybot/build-light-sensor-circuits
*/

#include "simpletools.h"

int lightLeft, lightRight;

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

    print("%clightLeft = %d, lightRight = %d%c",
           HOME, lightLeft, lightRight, CLREOL);
    pause(250);
  }
}
