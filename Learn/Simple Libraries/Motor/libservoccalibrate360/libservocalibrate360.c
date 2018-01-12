#include "simpletools.h"
#include "servocalibrate360.h"    

int main()
{
  high(26);
  high(27);
  cal_servo360(12, 14);
  cal_servo360(13, 15);
  
  cal_displayData(12);
  cal_displayData(13);
  
  cal_displayResults(12);
  cal_displayResults(13);

  low(26);
  low(27);
}


