/* 
  ActivityBot Calibrate.c

  Calibrate the ActivityBot's servos and encoders

  https://learn.parallax.com/ab360
*/

#include "simpletools.h"
#include "abcalibrate360.h"    

int main()
{
  cal_servoPins(12, 13);
  cal_encoderPins(14, 15);
  
  high(26);
  high(27);
  cal_activityBot();
  low(26);
  low(27);
}
