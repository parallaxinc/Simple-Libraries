/* 

  ActivityBot Calibrate.c

  Calibrate the ActivityBot's servos and encoders

  http://learn.parallax.com/activitybot

*/

#include "simpletools.h"
#include "abcalibrate.h"    

int main()
{
  servo_pins(12, 13);
  encoder_pins(14, 15);

  high(26);
  high(27);
  cal_activityBot();
  low(26);
  low(27);
}
