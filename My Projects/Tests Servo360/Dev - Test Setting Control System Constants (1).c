/*
  I used this one to determine some nice angular control PID constants. 
*/


#include "simpletools.h"
#include "abdrive360.h"

void forwardStopBackwardStop(void);

int main()
{
  servo360_connect(12, 14);
  
  servo360_speed(12, 0);

  //servo360_setAngleCtrlSpeedMax(12, 180);
  servo360_setAngleCtrlSpeedMax(12, 360);
  //servo360_setAngleCtrlSpeedMax(12, 720);

  //  Use these!
  servo360_setControlSys(12, S360_KPA, 12000);     // New KPA
  servo360_setControlSys(12, S360_KIA, 600);       // New KIA
  servo360_setControlSys(12, S360_KDA, 6000);      // New KDA
  servo360_setControlSys(12, S360_IA_MAX, 600);    // New FB360_POS_INTGRL_MAX
  //

  //pause(500);
  servo360_consoleInit();
  //pause(1000);
  servo360_angle(12, 0);
  pause(3000);
  servo360_angle(12, 360);
  pause(6000);
  servo360_angle(12, -360);
  pause(8000);
  servo360_angle(12, 0);
  pause(3000);
  servo360_consolePause();
  servo360_angle(12, 0);
  pause(500);
  while(1);
}
