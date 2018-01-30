/*
   Dev - Velocity Control System Tuning (3).c
*/

#include "simpletools.h"
#include "abdrive360.h"

void forwardStopBackwardStop(void);

int main()
{
  drive_speed(0, 0);
  
  //  
  drive_setAcceleration(FOR_SPEED, 400);
  
  servo360_couple(12, 13);
  servo360_setCoupleScale(12, 13, 2000);

  servo360_setControlSys(12, S360_KPV, 500);            // KPV
  servo360_setControlSys(13, S360_KPV, 500);            // KPV
  servo360_setControlSys(12, S360_KIV, 000);             // KIV
  servo360_setControlSys(13, S360_KIV, 000);             // KIV
  servo360_setControlSys(12, S360_KDV, 0000);            // KDV
  servo360_setControlSys(13, S360_KDV, 0000);            // KDV
  servo360_setControlSys(12, S360_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX
  //

  int kpL = servo360_getControlSys(12, S360_KPV);
  int kpR = servo360_getControlSys(13, S360_KPV);
  int kiL = servo360_getControlSys(12, S360_KIV);
  int kiR = servo360_getControlSys(13, S360_KIV);
  int kdL = servo360_getControlSys(12, S360_KDV);
  int kdR = servo360_getControlSys(13, S360_KDV);
  int kiclL = servo360_getControlSys(12, S360_IV_MAX);
  int kiclR = servo360_getControlSys(13, S360_IV_MAX);

  print("kpL = %d, kpR = %d\r", kpL, kpR);
  print("kiL = %d, kiR = %d\r", kiL, kiR);
  print("kdR = %d, kdR = %d\r", kdL, kdR);
  print("kiclL = %d, kiclR = %d\r", kiclL, kiclR);
  
  // console* does nothing unless you uncomment #define _servo360_monitor_ in servo360.h 
  // and recompile libservo360.  Make sure to un-comment and recompile to save
  // memory.        
  servo360_consoleRun();  
   
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

  servo360_consoleEnd();

  pause(100);
}
