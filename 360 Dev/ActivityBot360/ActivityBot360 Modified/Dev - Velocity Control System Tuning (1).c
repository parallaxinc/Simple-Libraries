/*
   Accelleration FOR_SPEED, 300
*/


#include "simpletools.h"
#include "abdrive360.h"

void forwardStopBackwardStop(void);

int main()
{
  drive_speed(0, 0);
  //  
  drive_setAcceleration(FOR_SPEED, 200);

  servo360_setControlSys(12, S360_KPV, 3000);            // KPV
  servo360_setControlSys(13, S360_KPV, 3000);            // KPV
  servo360_setControlSys(12, S360_KIV, 500);             // KIV
  servo360_setControlSys(13, S360_KIV, 500);             // KIV
  servo360_setControlSys(12, S360_KDV, 1600);            // KDV
  servo360_setControlSys(13, S360_KDV, 1600);            // KDV
  servo360_setControlSys(12, S360_IV_MAX, 325);          // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 325);          // FB360_VEL_INTGRL_MAX
  //


  /*
  drive_setAcceleration(FOR_SPEED, 2400);

  servo360_setControlSys(12, S360_KPV, 0000);            // KPV
  servo360_setControlSys(13, S360_KPV, 0000);            // KPV
  servo360_setControlSys(12, S360_KIV, 000);             // KIV
  servo360_setControlSys(13, S360_KIV, 000);             // KIV
  servo360_setControlSys(12, S360_KDV, 0);            // KDV
  servo360_setControlSys(13, S360_KDV, 0);            // KDV
  servo360_setControlSys(12, S360_IV_MAX, 000);          // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 000);          // FB360_VEL_INTGRL_MAX
  */


  /*
  drive_setAcceleration(FOR_SPEED, 400);

  servo360_setControlSys(12, S360_KPV, 0000);            // KPV
  servo360_setControlSys(13, S360_KPV, 0000);            // KPV
  servo360_setControlSys(12, S360_KIV, 000);             // KIV
  servo360_setControlSys(13, S360_KIV, 000);             // KIV
  servo360_setControlSys(12, S360_KDV, 0);            // KDV
  servo360_setControlSys(13, S360_KDV, 0);            // KDV
  servo360_setControlSys(12, S360_IV_MAX, 0);          // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 0);          // FB360_VEL_INTGRL_MAX
  */

  int kpL = servo360_getControlSys(12, S360_KPV);
  int kpR = servo360_getControlSys(13, S360_KPV);
  int kiL = servo360_getControlSys(12, S360_KIV);         // KIV
  int kiR = servo360_getControlSys(13, S360_KIV);         // KIV
  int kdL = servo360_getControlSys(12, S360_KDV);         // KDV
  int kdR = servo360_getControlSys(13, S360_KDV);         // KDV
  int kiclL = servo360_getControlSys(12, S360_IV_MAX);    // FB360_VEL_INTGRL_MAX
  int kiclR = servo360_getControlSys(13, S360_IV_MAX);    // FB360_VEL_INTGRL_MAX

  print("kpL = %d, kpR = %d\r", kpL, kpR);
  print("kiL = %d, kiR = %d\r", kiL, kiR);
  print("kdR = %d, kdR = %d\r", kdL, kdR);
  print("kiclL = %d, kiclR = %d\r", kiclL, kiclR);
  
  // console* does nothing unless you uncomment #define _servo360_monitor_ in servo360.h 
  // and recompile libservo360.  Make sure to un-comment and recompile to save
  // memory.        
  servo360_consoleRun();  
   
  drive_speed(46, 46);
  pause(4000);
  drive_speed(0, 0);
  pause(1000);
  /*
  drive_speed(32, -32);
  pause(850);
  drive_speed(0, 0);
  pause(500);
  drive_speed(-32, 32);
  pause(1700);
  drive_speed(0,0);
  pause(500);
  drive_speed(32, -32);
  pause(850);
  drive_speed(0, 0);
  pause(500);
  */
  drive_speed(-46, -46);
  pause(4000);
  drive_speed(0, 0);
  pause(1000);

  servo360_consoleEnd();

  pause(100);
  
}
