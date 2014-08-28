/*
  Test Encoder Connections.c

  Load to ActivityBot EEPROM. PWR to Position 2.
  Gently turn each wheel by hand.  Right wheel
  blinks P27 LED, left wheel blinks P26 LED.
  If not, encoders are not seeing wheel spokes.
  Go to Extras/Troubleshooting section of tutorial.

  http://learn.parallax.com/activitybot/test-encoder-connections
*/

#include "simpletools.h"

int main()                    
{
  low(26);
  low(27);
  while(1)
  {
    set_output(26, input(14));
    set_output(27, input(15));
  }
}

