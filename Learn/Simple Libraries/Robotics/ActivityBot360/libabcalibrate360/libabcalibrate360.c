#include "simpletools.h"
#include "abcalibrate360.h"    

int main()
{
  high(26);
  high(27);
  //cal_activityBot();
  low(26);
  low(27);
  
  //cal_servoPins(12, 13);
  //cal_encoderPins(14, 15);
  //cal_displayData();
  cal_displayResults();
  //cal_clear();
}