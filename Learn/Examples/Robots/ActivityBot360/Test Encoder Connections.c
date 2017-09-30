/*
  Test Encoder Connections.c

  Load to ActivityBot EEPROM. PWR to Position 2.
  Gently turn each wheel by hand.  Right wheel
  blinks P27 LED, left wheel blinks P26 LED.
  If not, encoders are not measuring rotation.
  Go to Extras/Troubleshooting section of tutorial.

  http://learn.parallax.com/activitybot/test-encoder-connections
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  low(26);
  low(27);
  while(1)
  {
    int ticksLeft, ticksRight;
    drive_getTicks(&ticksLeft, &ticksRight);
    set_output(26, ticksLeft % 2);
    set_output(27, ticksRight % 2);
  }
}

