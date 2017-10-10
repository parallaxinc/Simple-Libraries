/* 
  drive_goto variations.c

  This code demonstrates the problem in ActivityBots with servos that both have 
  the similar zero speed deadband offsets near the allowable limits. Example 
  instead of 1480 to 1520, both servos hare 1490 to 1530 us zero speed deadbands.

  The monitor (with SimpleIDE Terminal) functions have no effect unless you build 
  the libservo360 project with this un-commented:

    #define _servo360_monitor_

  For best results, use the Parallax WX ESP8266 WiFi Module - DIP for programming
  and terminal display.  
  https://www.parallax.com/product/32420d

  Make sure to re-comment it when done because it takes a signfiicant program memory.
  
*/

#include "simpletools.h"
#include "abdrive360.h"

int main()                    
{
  drive_speed(0, 0);
  pause(1000);
  servo360_monitorRun();
  pause(1000);
  
  /*
  servo360_setTransferFunction(12, S360_SETTING_VM_CCW, 202);
  servo360_setTransferFunction(12, S360_SETTING_VB_CCW, 280);
  
  servo360_setTransferFunction(12, S360_SETTING_VM_CW, 215);
  servo360_setTransferFunction(12, S360_SETTING_VB_CW, -126 );

  servo360_setTransferFunction(13, S360_SETTING_VM_CCW, 204 );
  servo360_setTransferFunction(13, S360_SETTING_VB_CCW, 273);

  servo360_setTransferFunction(13, S360_SETTING_VM_CW, 214);
  servo360_setTransferFunction(13, S360_SETTING_VB_CW, -146);
  */


  servo360_setTransferFunction(12, S360_SETTING_VM_CCW, 204);
  servo360_setTransferFunction(12, S360_SETTING_VB_CCW, 273);
  
  servo360_setTransferFunction(12, S360_SETTING_VM_CW, 215);
  servo360_setTransferFunction(12, S360_SETTING_VB_CW, -133 );

  servo360_setTransferFunction(13, S360_SETTING_VM_CCW, 204 );
  servo360_setTransferFunction(13, S360_SETTING_VB_CCW, 253);

  servo360_setTransferFunction(13, S360_SETTING_VM_CW, 215);
  servo360_setTransferFunction(13, S360_SETTING_VB_CW, -146);


  drive_goto(192, 192);
  pause(1000);
  drive_goto(-28, 28);
  pause(1000);
  drive_goto(28 * 2, -28 * 2);
  pause(1000);
  drive_goto(-28, 28);
  pause(1000);
  drive_goto(-192, -192);
  pause(1000);

  drive_goto(128, 192);
  pause(1000);
  drive_goto(-128, -192);
  pause(1000);
  drive_goto(192, 128);
  pause(1000);
  drive_goto(-192, -128);
  pause(1000);
  
  servo360_monitorEnd();
}