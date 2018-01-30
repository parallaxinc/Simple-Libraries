/*
  Roaming with Whiskers.c

  Go forward until object detected by whisker(s).  Then, back up, turn
  and go a new direction.

  http://learn.parallax.com/activitybot/roaming-whiskers
*/

#include "simpletools.h"                        // Include simpletools library
#include "abdrive360.h"                            // Include abdrive library

int main()                                      // main function
{
  freqout(4, 2000, 3000);                       // Speaker tone: 2 s, 3 kHz

  drive_speed(0, 0);                      // Go forward

  drive_setAcceleration(FOR_SPEED, 600);

  servo360_setCoupleScale(12, 13, 2000);

  servo360_setControlSys(12, S360_KPV, 500);            // KPV
  servo360_setControlSys(13, S360_KPV, 500);            // KPV
  servo360_setControlSys(12, S360_KIV, 000);             // KIV
  servo360_setControlSys(13, S360_KIV, 000);             // KIV
  servo360_setControlSys(12, S360_KDV, 0000);            // KDV
  servo360_setControlSys(13, S360_KDV, 0000);            // KDV
  servo360_setControlSys(12, S360_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(13, S360_IV_MAX, 0);            // FB360_VEL_INTGRL_MAX

  
  
  while(1)                                      // Main loop
  {
    // Go forward for 1/50th of a second.
    drive_speed(64, 64);                      // Go forward

    // Check whisker states.
    int wL = input(7);                          // Left whisker -> wL variable
    int wR = input(8);                          // Right whisker -> wR variable

    // If whisker(s) pressed, avoid obstacle.
    if(wR == 0)                                 // Just right whisker
    {
      drive_speed(-64, -64);                  // Back up 0.5 seconds
      pause(500);
      drive_speed(-64, 64);                   // Turn left 0.22 seconds
      pause(220);
    }
    else if(wL == 0)                            // Just left whisker
    {
      drive_speed(-64, -64);                  // Back up 0.5 seconds
      pause(500);
      drive_speed(64, -64);                   // Turn right 0.25 seconds
      pause(220);
    }
  }
}
