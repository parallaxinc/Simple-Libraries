/*
   Velocity Control System Tuning.c
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()
{
  drive_speed(0, 0);
  
  //  
  drive_setAcceleration(FOR_SPEED, 600);
  
  servo360_couple(12, 13);
  servo360_setCoupleScale(12, 13, 2000);

  servo360_setControlSys(12, S360_SETTING_KPV, 500);             // KPV
  servo360_setControlSys(13, S360_SETTING_KPV, 500);             // KPV
  servo360_setControlSys(12, S360_SETTING_KIV, 0);               // KIV
  servo360_setControlSys(13, S360_SETTING_KIV, 0);               // KIV
  servo360_setControlSys(12, S360_SETTING_KDV, 0);               // KDV
  servo360_setControlSys(13, S360_SETTING_KDV, 0);               // KDV
  servo360_setControlSys(12, S360_SETTING_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_SETTING_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX
  //

  int kpL = servo360_getControlSys(12, S360_SETTING_KPV);
  int kpR = servo360_getControlSys(13, S360_SETTING_KPV);
  int kiL = servo360_getControlSys(12, S360_SETTING_KIV);
  int kiR = servo360_getControlSys(13, S360_SETTING_KIV);
  int kdL = servo360_getControlSys(12, S360_SETTING_KDV);
  int kdR = servo360_getControlSys(13, S360_SETTING_KDV);
  int kiclL = servo360_getControlSys(12, S360_SETTING_IV_MAX);
  int kiclR = servo360_getControlSys(13, S360_SETTING_IV_MAX);

  print("kpL = %d, kpR = %d\r", kpL, kpR);
  print("kiL = %d, kiR = %d\r", kiL, kiR);
  print("kdR = %d, kdR = %d\r", kdL, kdR);
  print("kiclL = %d, kiclR = %d\r", kiclL, kiclR);
  
  // monitor* does nothing unless you uncomment #define _servo360_monitor_ in servo360.h 
  // and recompile it.  Make sure to recomment and recompile to save program memory.        
  // Also, make sure to call monitor_end before making any print calls.
  servo360_monitorRun();  
   
  drive_speed(64, 64);
  pause(4000);
  drive_speed(0, 0);
  pause(1000);
  
  /*
  drive_speed(42, -42);
  pause(600);
  drive_speed(0, 0);
  pause(700);
  drive_speed(-42, 42);
  pause(1200);
  drive_speed(0,0);
  pause(700);
  drive_speed(42, -42);
  pause(600);
  drive_speed(0, 0);
  pause(700);
  */

  drive_speed(-64, -64);
  pause(4000);
  drive_speed(0, 0);
  pause(1000);

  servo360_monitorEnd();

  pause(100);
}
