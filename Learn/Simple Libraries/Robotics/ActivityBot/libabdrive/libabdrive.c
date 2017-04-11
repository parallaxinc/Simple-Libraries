//#define _monitor_

// from dev 74

/* 
  Forward Stop Face Right.c

  http://learn.parallax.com/activitybot/go-certain-distances
*/
/*  MONITOR
    print("n%d\r"\
        "dLf%d dLc%d dL%d sLT%d sL%d tgL%d gtfL%d scL%d"\
        " | "\
        "dRf%d dRc%d dR%d sRT%d sR%d tgR%d gtfR%d scR%d\r"\
        "rsl%d dald%d | rsr%d dalr%d\r",
        _servoPulseReps, 
        abd_ticksLf, abd_dlc, abd_ticksL, abd_speedLT, abd_speedL, abd_ticksGuardL, abd_gotoFlagL, abd_stopCtrL, 
        abd_ticksRf, abd_drc, abd_ticksR, abd_speedRT, abd_speedR, abd_ticksGuardR, abd_gotoFlagR, abd_stopCtrR, 
        abd_rampStepL, abd_ditherALd, abd_rampStepR, abd_ditherARd);
*/ 

/*
    sprint(abd_str, "\r\rddL%d, spdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d | "\
          "ddR%d, spdLimL=%d, rmpStpL=%d dthrAL=%d, dthrVL=%d\r\r",
          left, abd_speedLimitL, abd_rampStepL, abd_ditherAL, abd_ditherVL,
          right, abd_speedLimitR, abd_rampStepR, abd_ditherAR, abd_ditherVR
          );// 
*/

#include "simpletools.h"
#include "abdrive.h"

int main()                    
{
  print("%c", CLS);
  //while(1);
  //drive_setMaxSpeed(64);
  #ifdef _monitor_
    encoderLeds_start(26, 27);
    pause(1000);
    monitor_start(3000);
  #endif
  //print("hello");
  
  //drive_setMaxSpeed(128);
  //drive_setAcceleration(400);
  //drive_setMaxSpeed(96);
  //drive_setAcceleration(300);
/*  
  drive_speed(128, 128);
  pause(3000);
  //drive_speed(0, 0);

  drive_speed(-128, -128);
  pause(3000);
  drive_speed(0, 0);
  
  int left, right;
  drive_getTicks(&left, &right);
  
  drive_goto(-left, -right);
*/  
  drive_goto(128, 128);
  //pause(200);
  //drive_goto(32, -32);
  //pause(200);
  //drive_goto(-32, 32);
  //pause(200);
  drive_goto(-128, -128);
  
  
  drive_goto(128, 192);
  //pause(200);
  drive_goto(-128, -192);
  //pause(200);
  drive_goto(192, 128);
  //pause(200);
  drive_goto(-192, -128);
  
  
  pause(1000);
  
  
  #ifdef _monitor_
  monitor_stop();
  #endif
  
  while(1);
  
  
  drive_speed(128, 128);
  pause(1000);
  drive_speed(-128, -128);
  pause(1300);
  drive_speed(0, 0);
  
  pause(1000);

  drive_speed(128, 96);
  pause(1000);
  drive_speed(-128, -96);
  pause(1300);
  drive_speed(0, 0);
  
  drive_speed(96, 128);
  pause(1000);
  drive_speed(-96, -128);
  pause(1300);
  drive_speed(0, 0);

  pause(1000);

  #ifdef _monitor_
  monitor_stop();
  #endif
  while(1);

  /*
  pause(1000);
  drive_speed(-64, -96);
  pause(1500);
  drive_speed(64, 96);
  pause(1500);
  drive_speed(-96, -64);
  pause(1500);
  drive_speed(96, 64);
  pause(1500);
  drive_speed(-96, 64);
  pause(1500);
  drive_speed(96, -64);
  pause(1500);
  drive_speed(-64, 96);
  pause(1500);
  drive_speed(64, -96);
  pause(1500);
  drive_speed(0, 0);
  */
}

