#include "simpletools.h"
#include "abcalibrate360.h"   
#include "abdrive360.h" 

/*
void cal_fail_song(void)
{
  freqout(4, 175, 1275);
  pause(150);
  freqout(4, 500, 850);
  pause(100);
}
*/

int main()
{
  
  high(26);
  high(27);
  cal_activityBot();
  low(26);
  low(27);
  
  //cal_displayData();
  //cal_displayResults();
  //cal_servoPins(12, 13);
  //cal_encoderPins(14, 15);
  //cal_clear();
  
  //drive_goto(128, 128);
  
}