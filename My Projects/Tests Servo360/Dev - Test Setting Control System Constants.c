/*
  WARNING: Dev - Test Setting Control System Constants demonstrates detuning 
  for unstable control system states because those are readily observable.  
  Make sure to comment the detuning before running so as not to apply undue 
  stress to ActivityBot servos.  If you experiment with tuning, and generally,
  stick closer to the defaults than the example program does. 
*/


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
  
  // Defaults as of 9/22/17 at 5:30 PM PDT
  // Subject to change
  servo360_setControlSys(12, S360_KPA, 5000);       // KPA
  servo360_setControlSys(13, S360_KPA, 5000);     
  servo360_setControlSys(12, S360_KIA, 200);       // KIA
  servo360_setControlSys(13, S360_KIA, 200);
  servo360_setControlSys(12, S360_KDA, -100);      // KDA
  servo360_setControlSys(13, S360_KDA, -100);
  servo360_setControlSys(12, S360_IA_MAX, 500);    // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 500);
  
  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Go overboard with integration.  Oscillatory behavior should be
  // very noticeable.
  servo360_setControlSys(12, S360_KPA, 5000);       // KPA
  servo360_setControlSys(13, S360_KPA, 5000);     
  servo360_setControlSys(12, S360_KIA, 200 * 4);
  servo360_setControlSys(13, S360_KIA, 200 * 4);
  servo360_setControlSys(12, S360_KDA, -100);       // KDA
  servo360_setControlSys(13, S360_KDA, -100);
  servo360_setControlSys(12, S360_IA_MAX, 500 * 4);
  servo360_setControlSys(13, S360_IA_MAX, 500 * 4);
  
  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Restore integration to default, eliminate derivative, overdo proprotional.
  // Result should be more jittery.
  servo360_setControlSys(12, S360_KPA, 5000 * 4);
  servo360_setControlSys(13, S360_KPA, 5000 * 4);     
  servo360_setControlSys(12, S360_KIA, 200);       // KIA
  servo360_setControlSys(13, S360_KIA, 200);
  servo360_setControlSys(12, S360_KDA, 0);
  servo360_setControlSys(13, S360_KDA, 0);
  servo360_setControlSys(12, S360_IA_MAX, 500);    // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 500);

  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  // Defaults
  servo360_setControlSys(12, S360_KPA, 5000);       // KPA
  servo360_setControlSys(13, S360_KPA, 5000);     
  servo360_setControlSys(12, S360_KIA, 200);       // KIA
  servo360_setControlSys(13, S360_KIA, 200);
  servo360_setControlSys(12, S360_KDA, -100);      // KDA
  servo360_setControlSys(13, S360_KDA, -100);
  servo360_setControlSys(12, S360_IA_MAX, 500);    // FB360_POS_INTGRL_MAX
  servo360_setControlSys(13, S360_IA_MAX, 500);
  

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

