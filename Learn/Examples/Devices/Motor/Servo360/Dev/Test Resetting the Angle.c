/*
  Applications that calculate beyond +/- 12^31 4096ths of a full circle
  can cause trouble.  The binary overflow for speed or goto occurs at
  
  (2^31 - 1) / 2^12 = (2^19 - 1) = 524,287 turns.
  524,287 turns * (1 s / 2 turns) * (1 min / 60 s) * (1 hr / 60 min) 
  = 72.8 hours at top speed  

  For angle targets, the overflow boundary is 1 / units full circle that 
  far.  For exmaple, with 360 degree units in a full circle, the max turns
  would be 524,287 / 360.  
  
  This test uses servo360_setTurns to move the number of turns forward and
  then back again, testing between each operation.  

  The fb360_consoleInit function only displays if you uncumment 
  #define _servo360_monitor_ in servo360.h and recompile.  To keep program sizes 
  reasonable, make sure to re-comment and recompile after this teset.
  Do not call any print functions after calling servo360_monitor_init.  
*/  

#include "simpletools.h"
#include "abdrive360.h"

void displayStuff(void);

int main()
{

  // Speed settings are not prone to overflow, so we can get close 
  // to the overflow edge without falling over.

  drive_speed(0, 0);
  
  //servo360_consoleRun();
  
  servo360_setTurns(12, 500000);
  pause(100);
  
  drive_speed(32, 32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  
  servo360_setTurns(12, -500000);
  pause(100);
  
  drive_speed(-32, -32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  

  // In angle calculations, it is only safe to go to 
  // max turns / units in a circle.

  servo360_angle(12, 0);
  servo360_angle(13, -0);
  pause(3000);
  
  servo360_setTurns(12, (500000 / 64));
  pause(100);
  
  int angle = servo360_getAngle(12);

  servo360_angle(12, angle + 32);
  servo360_angle(13, -32);
  pause(3000);
  
  servo360_setTurns(12, (-500000 / 64));
  pause(100);
  
  servo360_angle(12, -32);
  servo360_angle(13, 32);
  pause(3000);
  

  // Goto settings currently do not require angle recalculations. 
  // They only calculate offsets from current angles, so they are
  // about as forgiving as speeds.

  drive_goto(0, 0);

  servo360_setTurns(12, 500000);
  pause(100);
  
  drive_goto(32, 32);
  pause(500);
  
  servo360_setTurns(12, -500000);
  pause(100);
  
  drive_goto(-32, -32);
  pause(2000);
  
  // Now, check jumping negative and then back to zero.
  
  // Speed settings.

  drive_speed(0, 0);
  
  //servo360_consoleRun();
    
  servo360_setTurns(12, -500000);
  pause(100);
  
  drive_speed(32, 32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  
  servo360_setTurns(12, 500000);
  pause(100);
  
  drive_speed(-32, -32);
  pause(2000);
  drive_speed(0, 0);
  pause(500);
  

  //Angle settings.

  servo360_angle(12, 0);
  servo360_angle(13, 0);
  pause(3000);
  
  servo360_setTurns(12, (-500000 / 64));
  pause(100);
  
  angle = servo360_getAngle(12);

  servo360_angle(12, angle + 32);
  servo360_angle(13, -32);
  pause(3000);
  
  servo360_setTurns(12, (500000 / 64));
  pause(100);
  
  servo360_angle(12, -32);
  servo360_angle(13, 32);
  pause(3000);
  

  // Goto settings.

  drive_goto(0, 0);

  servo360_setTurns(12, -500000);
  pause(100);
  
  drive_goto(32, 32);
  pause(500);
  
  servo360_setTurns(12, 500000);
  pause(100);
  
  drive_goto(-32, -32);
  pause(2000);
  
}  

