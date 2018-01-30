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
  

  servo360_setTransferFunction(12, S360_SETTING_VB_CCW, 250);
  servo360_setTransferFunction(12, S360_SETTING_VB_CW, -75);
  servo360_setTransferFunction(13, S360_SETTING_VB_CCW, 250 );
  servo360_setTransferFunction(13, S360_SETTING_VB_CW, -75);


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