#include "simpletools.h"
#include "abcalibrate.h"    

int main()
{
  high(26);
  high(27);
  cal_activityBot();
  cal_displayData();
  cal_displayResults();
  low(26);
  low(27);
}


