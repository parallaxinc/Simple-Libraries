/*
  Test Light Sensors.c

  https://learn.parallax.com/ab360
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
