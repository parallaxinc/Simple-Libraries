#include "simpletools.h"
#include "servo360.h"

void testSetAngle(int pin, int degrees, int msHold);

int main()
{
  servo360_connect(12, 14);
  
  /* // Defaults
  servo360_setControlSys(12, S360_SETTING_KPA, 12000);
  servo360_setControlSys(12, S360_SETTING_KIA, 600);
  servo360_setControlSys(12, S360_SETTING_KDA, 6000);
  servo360_setControlSys(12, S360_SETTING_IA_MAX, 150);
  */

  servo360_setControlSys(12, S360_SETTING_KPA, 8000);  // Try reducing this
  servo360_setControlSys(12, S360_SETTING_KIA, 600);
  servo360_setControlSys(12, S360_SETTING_KDA, 6000);
  servo360_setControlSys(12, S360_SETTING_IA_MAX, 150);

  int kpL = servo360_getControlSys(12, S360_SETTING_KPA);
  int kiL = servo360_getControlSys(12, S360_SETTING_KIA);
  int kdL = servo360_getControlSys(12, S360_SETTING_KDA);
  int kiclL = servo360_getControlSys(12, S360_SETTING_IA_MAX);

  print("kpL = %d\r", kpL);
  print("kiL = %d\r", kiL);
  print("kdR = %d\r", kdL);
  print("kiclL = %d\r\r", kiclL);
  
  testSetAngle(12, 90, 3000);
  testSetAngle(12, -90, 3000);
  testSetAngle(12, 180, 3000);
  testSetAngle(12, -180, 3000);
}

void testSetAngle(int pin, int degrees, int msHold)
{
  print("target = %d", degrees);
  servo360_angle(pin, degrees);
  pause(msHold);
  int measured = servo360_getAngle(pin);
  print(", measured = %d\r", measured);
}  
