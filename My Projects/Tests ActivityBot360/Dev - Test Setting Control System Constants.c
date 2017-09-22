#include "simpletools.h"
#include "abdrive360.h"

void forwardStopBackwardStop(void);

int main()
{
  drive_speed(0, 0);
  pause(100);
  
  // To use this, recompile libservo360 with #define _console_ uncommented
  // in servo360.h
  //
  #ifdef _console_
    console_start();
    suppressFbDisplay = 0;
  #endif 
  // 
  
  pause(1000);
  
  // Defaults
  servo360_setControlSys(12, S360_KPV, 1200);     // KPV
  servo360_setControlSys(13, S360_KPV, 1200);     
  servo360_setControlSys(12, S360_KIV, 225);      // KIV
  servo360_setControlSys(13, S360_KIV, 225);
  servo360_setControlSys(12, S360_KDV, -100);     // KDV
  servo360_setControlSys(13, S360_KDV, -100);
  servo360_setControlSys(12, S360_IV_MAX, 350);   // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 350);
  
  forwardStopBackwardStop();
  
  // Go overboard with integration.  Oscillatory behavior should be
  // very noticeable.
  servo360_setControlSys(12, S360_KPV, 1200);     // KPV
  servo360_setControlSys(13, S360_KPV, 1200);     
  servo360_setControlSys(12, S360_KIV, 600);
  servo360_setControlSys(13, S360_KIV, 600);
  servo360_setControlSys(12, S360_KDV, -100);
  servo360_setControlSys(13, S360_KDV, -100);
  servo360_setControlSys(12, S360_IV_MAX, 600);
  servo360_setControlSys(13, S360_IV_MAX, 600);

  forwardStopBackwardStop();
  
  // Restore integration to default, eliminate derivative, overdo proprotional.
  // Result should be more jittery.
  servo360_setControlSys(12, S360_KPV, 5000);     
  servo360_setControlSys(13, S360_KPV, 5000);     
  servo360_setControlSys(12, S360_KIV, 225);      // KIV
  servo360_setControlSys(13, S360_KIV, 225);
  servo360_setControlSys(12, S360_KDV, 0);        // KDV
  servo360_setControlSys(13, S360_KDV, 0);
  servo360_setControlSys(12, S360_IV_MAX, 350);   // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 350);

  forwardStopBackwardStop();
  
  // Defaults
  servo360_setControlSys(12, S360_KPV, 1200);     // KPV
  servo360_setControlSys(13, S360_KPV, 1200);     
  servo360_setControlSys(12, S360_KIV, 225);      // KIV
  servo360_setControlSys(13, S360_KIV, 225);
  servo360_setControlSys(12, S360_KDV, -100);     // KDV
  servo360_setControlSys(13, S360_KDV, -100);
  servo360_setControlSys(12, S360_IV_MAX, 350);   // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 350);

  pause(1000);
  // Angle holding tests
  
  // Defaults
  servo360_setControlSys(12, S360_KPA, 600);      // KPA
  servo360_setControlSys(13, S360_KPA, 600);     
  servo360_setControlSys(12, S360_KIA, 100);      // KIA
  servo360_setControlSys(13, S360_KIA, 100);
  servo360_setControlSys(12, S360_KDA, -200);      // KDA
  servo360_setControlSys(13, S360_KDA, -200);
  servo360_setControlSys(12, S360_IA_MAX, 350);   // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 350);
  
  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Go overboard with integration.  Oscillatory behavior should be
  // very noticeable.
  servo360_setControlSys(12, S360_KPA, 800);      // KPA
  servo360_setControlSys(13, S360_KPA, 800);     
  servo360_setControlSys(12, S360_KIA, 200 * 4);
  servo360_setControlSys(13, S360_KIA, 200 * 4);
  servo360_setControlSys(12, S360_KDA, 400);      // KDA
  servo360_setControlSys(13, S360_KDA, 400);
  servo360_setControlSys(12, S360_IA_MAX, 350 * 4);
  servo360_setControlSys(13, S360_IA_MAX, 350 * 4);
  
  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Restore integration to default, eliminate derivative, overdo proprotional.
  // Result should be more jittery.
  servo360_setControlSys(12, S360_KPA, 800 * 4);
  servo360_setControlSys(13, S360_KPA, 800 * 4);     
  servo360_setControlSys(12, S360_KIA, 200);      // KIA
  servo360_setControlSys(13, S360_KIA, 200);
  servo360_setControlSys(12, S360_KDA, 0);
  servo360_setControlSys(13, S360_KDA, 0);
  servo360_setControlSys(12, S360_IA_MAX, 350);   // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 350);

  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Defaults
  servo360_setControlSys(12, S360_KPA, 600);      // KPA
  servo360_setControlSys(13, S360_KPA, 600);     
  servo360_setControlSys(12, S360_KIA, 100);      // KIA
  servo360_setControlSys(13, S360_KIA, 100);
  servo360_setControlSys(12, S360_KDA, -200);      // KDA
  servo360_setControlSys(13, S360_KDA, -200);
  servo360_setControlSys(12, S360_IA_MAX, 350);   // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 350);
  

  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);

  #ifdef _console_
  suppressFbDisplay = 1;
  #endif
  
}

void forwardStopBackwardStop(void)
{
  drive_speed(32, 32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  drive_speed(-32, -32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
}  

