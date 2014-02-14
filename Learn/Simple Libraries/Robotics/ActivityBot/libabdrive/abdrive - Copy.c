/*
  abdrive.c library source
*/


#include "abdrive.h"                   // Include servo lib funct defs
#include "simpletools.h"
#include "simpletext.h"
#include "fdserial.h"
#include <string.h>

/*
  #ifdef interactive_development_mode
  dprint(xbee, "B After ramp distRampL = %d\n", distRampL);
  #endif
*/


void drive_com(int arrayLcnt, int arrayRcnt, 
               int centerL, int centerR, 
               int* pwAddrL, int* pwAddrR, 
               int* spdAddrL, int* spdAddrR);
void drive_set(int left, int right);
void encoders(void *par);
void interpolate(int* ltmp, int* rtmp);
void interpolation_table_setup();
void servos_diffDrive(void);
void drive_record(int startStop);
void drive_displayControlSystem(int start, int end);
void set_drive_speed(int left, int right);

static int cog = 0;
static int servoCog2 = 0;
static unsigned int stack[(160 + (250 * 4)) / 4];
//static unsigned int servoStack[(160 + (150 * 4)) / 4];

static int rampStep = 4;
static int speedLimit = 128;

static int spdrL[120];
static int spdmL[120];
static int spdrR[120];
static int spdmR[120];
static int a = 0;
static int r = 0;

static int eeAddr;
//static int intTabSetup = 0;
//static int eeStarted = 0;

static volatile int trimctr = 0;
static volatile int trimticksF = 0;
static volatile int trimticksB = 0;
static volatile int trimFL, trimFR, trimBL, trimBR, trimticksF, trimticksB;
static volatile int dca, trimticks;

static volatile int leftPrev, rightPrev;

static volatile int edL;                                      // error distance left
static volatile int edR;                                      // error distance right

static volatile int pL;                                       // proportional left
static volatile int pR;                                       // proportional right

static volatile int iL;                                   // integral left
static volatile int iR;                                   // integral right

static volatile int eaL = 0;
static volatile int eaR = 0;

static volatile int us;
static volatile int kp[6];

static volatile int sPinL = 12, sPinR = 13;   // Global variables
static volatile int ePinL = 14, ePinR = 15;
static volatile int tcL;
static volatile int tcR;
static volatile int tiL;
static volatile int ticksL = 0;
static volatile int ticksR = 0;

static volatile int record = 0;               // Record values to an array

#ifdef interactive_development_mode
static volatile int rv[2600];
#endif // interactive_development_mode

static volatile int ridx = 0;

static volatile int speedL;      // Requested servo speed left
static volatile int speedR;      // Requested servo speed right

static volatile int tiR;

static volatile int stateL;
static volatile int stateR;

static volatile int elCntL;
static volatile int elCntR;
static volatile int cntrLidx;
static volatile int cntrRidx;
static volatile int cntrLval;
static volatile int cntrRval;
static volatile int* pwL;
static volatile int* pwR;
static volatile int* spdL;
static volatile int* spdR;

static volatile int etpsR;    // encoder ticks per second requested right
static volatile int etpsL;    // encoder ticks per second requested right

static volatile int dlc;      // distance left calculated
static volatile int drc;      // distance right calculated
static volatile int pcount;
volatile unsigned int _servoPulseReps;
static volatile unsigned int _sprOld;
static volatile unsigned int _sprNext;


static volatile int ssiL; // servo speeed interpolated left
static volatile int ssiR; // servo speeed interpolated right

static volatile int driveL;
static volatile int driveR;

static volatile int phsL;
static volatile int phsR;
static volatile int phsLr;
static volatile int phsRr;

static int trimFunction = 1;
static int encoderFeedback = 1;
static int intTabSetup = 0;

static volatile int dlca = 0;                                 // distance left calculated (accumulated)
static volatile int drca = 0;                                 // distance right calculated (accumulated)
static volatile int dsr = 400;

volatile int zeroDelay = ON;
static int speedLprev = 0, speedRprev = 0;

fdserial *xbee;
int xbee_setup = 0;


void drive_getTicks(int *left, int *right)
{
  *left = ticksL;
  *right = ticksR;
}

void drive_servoPins(int servoPinLeft, int servoPinRight)          // drivePins function
{
  sPinL = servoPinLeft;                                       // Local to global assignments
  sPinR = servoPinRight;
  if(!us) us = CLKFREQ/1000000; 

  if(!intTabSetup)
  {
    interpolation_table_setup();
  }
}


void drive_encoderPins(int encPinLeft, int encPinRight)          // drivePins function
{
  ePinL = encPinLeft;
  ePinR = encPinRight;
  if(!us) us = CLKFREQ/1000000; 

  if(!intTabSetup)
  {
    interpolation_table_setup();
  }
}


void drive_pins(int servoPinLeft, int servoPinRight, int encPinLeft, int encPinRight)          // drivePins function
{
  sPinL = servoPinLeft;                             // Local to global assignments
  sPinR = servoPinRight;
  ePinL = encPinLeft;
  ePinR = encPinRight;
  us = CLKFREQ/1000000; 

  if(!intTabSetup)
  {
    interpolation_table_setup();
  }
}


void drive_setMaxSpeed(int maxTicksPerSec)
{
  speedLimit = maxTicksPerSec;
}


void drive_setRampStep(int stepsize)
{
  rampStep = stepsize;
}


void drive_feedback(int enabled)
{
  encoderFeedback = enabled;
}


void drive_trim(int enabled)
{
  trimFunction = enabled;
}



void drive_com(int arrayLcnt, int arrayRcnt, 
               int centerL, int centerR, 
               int* pwAddrL, int* pwAddrR, 
               int* spdAddrL, int* spdAddrR)
{
  elCntL = arrayLcnt;
  elCntR = arrayRcnt;
  cntrLidx = centerL;
  cntrRidx = centerR;
  pwL = pwAddrL;
  pwR = pwAddrR;
  spdL = spdAddrL;
  spdR = spdAddrR;
  cntrLval = pwAddrL[cntrLidx];
  cntrRval = pwAddrR[cntrRidx];
}


#ifdef interactive_development_mode
void drive_displayInterpolation(void)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  if(!intTabSetup) interpolation_table_setup();
 
  dprint(xbee, "Left Servo\n");
  dprint(xbee, "elCntL = %d, cntrLidx = %d\n\n", elCntL, cntrLidx);
  for(int r = 0; r < elCntL; r++)
  {
    dprint(xbee, "r = %d, spdrL = %d, spdmL = %d, \n", r, spdrL[r], spdmL[r]);
  }
  
  dprint(xbee, "Right Servo\n");
  dprint(xbee, "\n\nelCntR = %d, cntrRidx = %d\n\n", elCntR, cntrRidx);
  for(int r = 0; r < elCntR; r++)
  {
    dprint(xbee, "r = %d, spdrR = %d, spdmR = %d, \n", r, spdrR[r], spdmR[r]);
  }
  //getchar();  
  //#endif
}
#endif // interactive_development_mode


#ifndef interactive_development_mode
void drive_displayInterpolation(void)
{
  if(!intTabSetup) interpolation_table_setup();
 
  print("=== LEFT SERVO ===\n\n");
  print("Table Entries = %d\nZero Speed Index = %d\n\n", elCntL, cntrLidx);
  print("Index\tServo Drive\tEncoder Ticks/Second\n");
  print("-----\t-----------\t--------------------\n");
  for(int r = 0; r < elCntL; r++)
  {
    print("%d\t%d\t\t%d\n", r, spdrL[r], spdmL[r]);
  }
  
  print("\n\n=== RIGHT SERVO ===\n\n");
  print("Table Entries = %d\nZero Speed Index = %d\n\n", elCntR, cntrRidx);
  print("Index\tServo Drive\tEncoder Ticks/Second\n");
  print("-----\t-----------\t--------------------\n");
  for(int r = 0; r < elCntR; r++)
  {
    print("%d\t%d\t\t%d\n", r, spdrR[r], spdmR[r]);
  }
  
  //getchar();  
  //#endif
}
#endif // interactive_development_mode


#ifdef interactive_development_mode
void drive_trimDisplay(void)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  if(!intTabSetup) interpolation_table_setup();

  dprint(xbee, "trimFL %d, trimFR %d, trimBL %d, trimBR %d, trimticksF %d, trimticksB %d\n",
         trimFL, trimFR, trimBL, trimBR, trimticksF, trimticksB);
}
#endif // interactive_development_mode


#ifndef interactive_development_mode
void drive_trimDisplay(void)
{
  if(!intTabSetup) interpolation_table_setup();

  print("trimFL %d, trimFR %d, trimBL %d, trimBR %d, trimticksF %d, trimticksB %d\n",
         trimFL, trimFR, trimBL, trimBR, trimticksF, trimticksB);
}
#endif // interactive_development_mode


void interpolation_table_setup()
{
  if(!us) us = CLKFREQ/1000000; 

  //ee_putStr("ActivjtyBot", 12, _ActivityBot_EE_Start_);
  //putStr("hello");

  char str[12];
  ee_getStr(str, 12, _ActivityBot_EE_Start_);
  ee_getStr(str, 12, _ActivityBot_EE_Start_);

  /*
  if(strcmp(str, "ActivityBot"))
  {
    putStr("Calibrate your ActivityBot first!\n");
    putStr("For info, go to learn.parallax.com/ActivityBot/Calibrate-Your-ActivityBot\n");
    //drive_feedback(0);
  }
  */

  eeAddr = _ActivityBot_EE_Start_ + _ActivityBot_EE_Left_;
  //print("left eeAddr = %d\n", eeAddr);
  int cntL = ee_getInt(eeAddr);
  eeAddr += 4;
  int zstartL = ee_getInt(eeAddr);
  eeAddr += 4;
  for(r = 0; r < cntL; r++)
  {
    spdrL[r] = ee_getInt(eeAddr);
    eeAddr+=4;
    spdmL[r] = ee_getInt(eeAddr);
    eeAddr += 4;  
  }
  eeAddr = _ActivityBot_EE_Start_ + _ActivityBot_EE_Right_;
  //print("right eeAddr = %d\n", eeAddr);
  int cntR = ee_getInt(eeAddr);
  eeAddr += 4;
  int zstartR = ee_getInt(eeAddr);
  eeAddr += 4;
  for(r = 0; r < cntR; r++)
  {
    spdrR[r] = ee_getInt(eeAddr);
    eeAddr+=4;
    spdmR[r] = ee_getInt(eeAddr);
    eeAddr += 4;  
  } 

  drive_com(cntL, cntR, zstartL, zstartR, spdrL, spdrR, spdmL, spdmR);

  eeAddr      =  _ActivityBot_EE_Start_ + _ActivityBot_EE_Trims_;
  //print("trims eeAddr = %d\n", eeAddr);
  trimFL      =  ee_getInt(eeAddr +  0);
  trimFR      =  ee_getInt(eeAddr +  4);
  trimBL      =  ee_getInt(eeAddr +  8);
  trimBR      =  ee_getInt(eeAddr + 12);
  trimticksF  =  ee_getInt(eeAddr + 16);
  trimticksB  =  ee_getInt(eeAddr + 20);

  intTabSetup = 1;
}


void drive_close()                             // driveStop function
{
  cogstop(cog - 1);
  cog = 0;
}


void drive_trimSet(int direction, int side, int value)
{
  if(direction >= AB_FORWARD)
  {
    trimticksF = value;
    if(side == AB_LEFT)
    {
      trimFL = 1; 
      trimFR = 0; 
    } 
    else if(side == AB_RIGHT)
    {
      trimFR = 1; 
      trimFL = 0; 
    }
    else 
    {
      trimFL = 0; 
      trimFR = 0;
    }
  }
  else if(direction <= AB_BACKWARD) 
  {
    trimticksB = value;
    if(side == AB_LEFT)
    {
      trimBL = 1; 
      trimBR = 0; 
    } 
    else if(side == AB_RIGHT)
    {
      trimBR = 1; 
      trimBL = 0; 
    }
    else 
    {
      trimBL = 0; 
      trimBR = 0;
    }
  }
  else
  {
    trimBL = 0; trimBR = 0; 
    trimFL = 0; trimFR = 0; 
    trimticksF = 0; trimticksB = 0;
  }
  eeAddr = _ActivityBot_EE_Start_ + _ActivityBot_EE_Trims_;
  ee_putInt(trimFL,     eeAddr +  0);
  ee_putInt(trimFR,     eeAddr +  4);
  ee_putInt(trimBL,     eeAddr +  8);
  ee_putInt(trimBR,     eeAddr + 12);
  ee_putInt(trimticksF, eeAddr + 16);
  ee_putInt(trimticksB, eeAddr + 20);
}


// To-do: What if current speed > speedLimit?
void drive_goto(int left, int right)
{
  int ticksLstart = ticksL;
  int ticksRstart = ticksR;
  int ticksLtarget = ticksLstart + left;
  int ticksRtarget = ticksRstart + right;
  int distRampL = 0, distRampR = 0, rampClampL = 0, rampClampR = 0, distCruiseL = 0, distCruiseR = 0;
  int tCruiseR = 0, tCruiseL = 0, speedReqL = 0, speedreqR = 0;
  int dt = 20;

  left *= 1000;
  right *= 1000;
  
  #ifdef interactive_development_mode
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  dprint(xbee, "---\n");
  #endif

  // Distance to ramp down if already going forward
  if(left > 0)
  {
    if(speedL)
    {
      for(int i = speedL; i > 0; i -= rampStep) distRampL += (i * dt);
    }
    #ifdef interactive_development_mode
    dprint(xbee, "F Before ramp distRampL = %d\n", distRampL);
    #endif
    for(int i = speedL; i <= speedLimit; i += rampStep)
    {
      if(i > speedLimit) i = speedLimit;
      distRampL += (i * dt * 2);
      rampClampL = i;
      if(left <= distRampL)
      {
        distRampL = left;
        break;
      }
    }
    #ifdef interactive_development_mode
    dprint(xbee, "F After ramp distRampL = %d\n", distRampL);
    #endif
  }
  if(right > 0)
  {
    if(speedR)
    {
      for(int i = speedR; i > 0; i -= rampStep) distRampR += (i * dt);
    }
    #ifdef interactive_development_mode
    dprint(xbee, "F Before ramp distRampR = %d\n", distRampR);
    #endif
    // Distance to ramp up/down
    for(int i = speedR; i <= speedLimit; i += rampStep)
    {
      if(i > speedLimit) i = speedLimit;
      distRampR += (i * dt * 2);
      rampClampR = i;
      if(right <= distRampR)
      {
        distRampR = right;
        break;
      }
    }
    #ifdef interactive_development_mode
    dprint(xbee, "F After ramp distRampR = %d\n", distRampR);
    #endif
  }
  /*
  dprint(xbee, "distRampL = %d\n", distRampL);
  dprint(xbee, "distCruiseL = %d\n", distCruiseL);
  dprint(xbee, "distCruiseL + distRampL = %d\n", distCruiseL + distRampL);
  dprint(xbee, "rampClampL = %d\n\n", rampClampL);

  dprint(xbee, "distRampR = %d\n", distRampR);
  dprint(xbee, "distCruiseR = %d\n", distCruiseR);
  dprint(xbee, "distCruiseR + distRampR = %d\n", distCruiseR + distRampR);
  dprint(xbee, "rampClampR = %d\n\n", rampClampR);
  */

  // Distance to ramp down if already going forward
  if(left < 0)
  {
    if(speedL)
    {
      for(int i = speedL; i < 0; i += rampStep) distRampL -= (i * dt);
    }
    #ifdef interactive_development_mode
    dprint(xbee, "B Before ramp distRampL = %d\n", distRampL);
    #endif
    for(int i = speedL; i >= -speedLimit; i -= rampStep)
    {
      if(i < -speedLimit) i = -speedLimit;
      distRampL += (i * dt * 2);
      rampClampL = i;
      if(left >= distRampL)
      {
        distRampL = left;
        break;
      }
    }
    #ifdef interactive_development_mode
    dprint(xbee, "B After ramp distRampL = %d\n", distRampL);
    #endif
  }
  //dprint(xbee, "distRampL = %d\n", distRampL);
  //while(1);
  if(right < 0)
  {
    if(speedR)
    {
      for(int i = speedR; i < 0; i += rampStep) distRampR -= (i * dt);
    }
    #ifdef interactive_development_mode
    dprint(xbee, "B Before ramp distRampR = %d\n", distRampR);
    #endif
    // Distance to ramp up/down
    for(int i = speedR; i >= -speedLimit; i -= rampStep)
    {
      if(i < -speedLimit) i = -speedLimit;
      distRampR += (i * dt * 2);
      rampClampR = i;
      if(right >= distRampR)
      {
        distRampR = right;
        break;
      }
    }
    #ifdef interactive_development_mode
    dprint(xbee, "B After ramp distRampR = %d\n", distRampR);
    #endif
  }



  //if(rampClampL > speedLimit) rampClampL = speedLimit;
  //if(rampClampR > speedLimit) rampClampR = speedLimit;
 
  //while(1);
  // Calculate distance & time full speed
  distCruiseL = left - distRampL;  
  distCruiseR = right - distRampR;  
  //tCruiseL = distCruiseL / speedLimit;
  //tCruiseR = distCruiseR / speedLimit;
  tCruiseL = distCruiseL / rampClampL;
  tCruiseR = distCruiseR / rampClampR;


  #ifdef interactive_development_mode
  dprint(xbee, "distRampL = %d\n", distRampL);
  dprint(xbee, "distCruiseL = %d\n", distCruiseL);
  dprint(xbee, "distCruiseL + distRampL = %d\n", distCruiseL + distRampL);
  dprint(xbee, "rampClampL = %d\n\n", rampClampL);

  dprint(xbee, "distRampR = %d\n", distRampR);
  dprint(xbee, "distCruiseR = %d\n", distCruiseR);
  dprint(xbee, "distCruiseR + distRampR = %d\n", distCruiseR + distRampR);
  dprint(xbee, "rampClampR = %d\n", rampClampR);
  #endif

  //Execute maneuver
  //while(0);
  //if(rampClampL) drive_ramp(rampClampL, rampClampR); 
  drive_ramp(rampClampL, rampClampR);

  if(rampClampL < 0 && tCruiseL > 0) pause(tCruiseL);
  if(rampClampL > 0 && tCruiseL > 0) pause(tCruiseL);


  //if(rampClampR < 0 && tCruiseR < 0) pause(-tCruiseR);
  //if(rampClampR > 0 && tCruiseR > 0) pause(tCruiseR);

  //if(tCruiseL > 0) pause(tCruiseL);                // To-Do remove left dependency
  drive_ramp(0, 0);

  pause(120);
  #ifdef interactive_development_mode
  dprint(xbee, "tCruiseL = %d\n\n", tCruiseL);
  #endif

  //while(1);

  // Correct for small errors
  //
  zeroDelay = OFF;


  dlc = ticksL;
  dlca = dlc * dsr;
  edL = 0;
  pL = 0;

  drc = ticksR;
  drca = drc * dsr;
  edR = 0;
  pR = 0;


  #ifdef interactive_development_mode
  dprint(xbee, "ticksL, ticksR before correction: %d, %d\n", ticksL, ticksR);
  #endif

  int reps = 0;
  int tempL = 0, tempR = 0;
  int tempTicks = _servoPulseReps;
  while(1)
  {
    while(tempTicks >= _servoPulseReps);

    if(ticksL > ticksLtarget)
    {
      tempL = -10;
      if(iL > 0) iL = 0;
    }
    else if (ticksL < ticksLtarget)
    {
      tempL = 10;
      if(iL < 0) iL = 0;
    }
    else 
    {
      tempL = 0;
      iL = 0;
    }

    if(ticksR > ticksRtarget)
    {
      tempR = -10;
      if(iR > 0) iR = 0;
    }
    else if (ticksR < ticksRtarget)
    {
      tempR = 10;
      if(iR < 0) iR = 0;
    }
    else 
    {
      tempR = 0;
      iR = 0;
    }
    drive_speed(tempL, tempR);
    
    if((ticksL == ticksLtarget) && (ticksR == ticksRtarget))
    {
      reps++;
    }
    else
    {
      reps = 0;
    }
    if(reps == 10) break;
  }
  drive_speed(0, 0);
  #ifdef interactive_development_mode
  dprint(xbee, "ticksL, ticksR after correction: %d, %d\n", ticksL, ticksR);
  #endif

  dlc = ticksL;
  dlca = dlc * dsr;
  edL = 0;
  pL = 0;

  drc = ticksR;
  drca = drc * dsr;
  edR = 0;
  pR = 0;

  zeroDelay = ON;
  //
}


//static int step = 6;
void drive_rampStep(int left, int right)
{
  int leftTemp, rightTemp;
  int sprOld = _servoPulseReps;

  if(left > speedL + rampStep) leftTemp = speedL + rampStep;
  else if(left < speedL - rampStep) leftTemp = speedL - rampStep;
  else leftTemp = left;

  if(right > speedR + rampStep) rightTemp = speedR + rampStep;
  else if(right < speedR - rampStep) rightTemp = speedR - rampStep;
  else rightTemp = right;

  drive_speed(leftTemp, rightTemp);
  while(sprOld >= _servoPulseReps);
  sprOld = _servoPulseReps;
}


//static int step = 6;
void drive_ramp(int left, int right)
{
  if(!intTabSetup)
  {
    interpolation_table_setup();
    set_drive_speed(0, 0);
    pause(40);
  }
  
  while((left != speedL) || (right != speedR))
  {
    drive_rampStep(left, right);
  }
}

/*
//static int step = 6;
void drive_ramp(int left, int right)
{
  #ifdef interactive_development_mode
  dprint(xbee, "drive_ramp(%d, %d)\n", left, right);
  #endif

  int leftTemp, rightTemp;
  int sprOld = _servoPulseReps;

  while((left != speedL) || (right != speedR))
  {
    if(left > speedL + rampStep) leftTemp = speedL + rampStep;
    else if(left < speedL - rampStep) leftTemp = speedL - rampStep;
    else leftTemp = left;
  
    if(right > speedR + rampStep) rightTemp = speedR + rampStep;
    else if(right < speedR - rampStep) rightTemp = speedR - rampStep;
    else rightTemp = right;
  
    drive_speed(leftTemp, rightTemp);
    while(sprOld >= _servoPulseReps);
    sprOld = _servoPulseReps;
  }
}
*/

void interpolate(int *ltmp, int *rtmp)
{
  
  int left = *ltmp;
  int right = *rtmp;

  /////printf("\netpsL = %d, etpsR = %d\n\n", etpsL, etpsR);

  int listep;
  int limit;
  int lookupval;

  if(left > 0)
  {
    listep = 1;
    limit = elCntL;
    lookupval = left;
  }
  else
  {
    listep = -1;
    limit = 0;
    lookupval = -left;
  }

  int rprev = cntrLidx;

  for(int r = cntrLidx; r != limit; r+=listep)
  {
    if(spdL[r] == lookupval)
    {
      left = pwL[r]; 
      break;
    }
    if((spdL[rprev] < lookupval) && (spdL[r] > lookupval))
    {
      int x = ((pwL[r]-pwL[rprev])*(lookupval-spdL[rprev]))/(spdL[r]-spdL[rprev]); 
      left = pwL[rprev] + x; 
      break;
    }
    rprev = r;
  }
  //if(r >= elCntL) left = pwL[elCntL];                    // 2013.08.17
  //if(r <= 0) left = pwL[0];                              // 2013.08.17
  //if(r >= elCntL) left = *ltmp;                    // 2013.08.17
  //if(r <= 0) left = *ltmp;                              // 2013.08.17

  if(right > 0)
  {
    listep = 1;
    limit = elCntL;
    lookupval = right;
  }
  else
  {
    listep = -1;
    limit = 0;
    lookupval = -right;
  }

  rprev = cntrRidx;

  for(int r = cntrRidx; r != limit; r+=listep)
  {
    if(spdR[r] == lookupval)
    {
      right = pwR[r]; 
      break;
    }
    if((spdR[rprev] < lookupval) && (spdR[r] > lookupval))
    {
      int x = ((pwR[r]-pwR[rprev])*(lookupval-spdR[rprev]))/(spdR[r]-spdR[rprev]); 
      right = pwR[rprev] + x; 
      break;
    }
    rprev = r;
  }
  //if(r >= elCntR) right = pwR[elCntR];                    // 2013.08.17
  //if(r <= 0) right = pwR[0];                              // 2013.08.17
  //if(r >= elCntR) right = *rtmp;                          // 2013.08.17
  //if(r <= 0) right = *rtmp;                               // 2013.08.17

  *ltmp = left;
  *rtmp = right;
}


void set_drive_speed(int left, int right)
{
  
  int leftTemp = left;
  int rightTemp = right;
  if((left <= 128) && (left >= -128) && (right <= 128) && (right >= -128))
  {
    interpolate(&leftTemp, &rightTemp);
  }
  else
  {
    if(left > 170) left = 170;
    if(left < -170) left = -170;
    if(right > 170) right = 170;
    if(right < -170) right = -170;
  }

  /*
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }
  dprint(xbee, "leftTemp = %d, rightTemp = %d\n", leftTemp, rightTemp);
  //dprint(xbee, "-(1500 + cntrLval) = %d, -(1500 - cntrRval) = %d\n", -(1500 + cntrLval), -(1500 - cntrRval));
  */


  /*
  if(encoderFeedback == 0)
  {
    if(speedLprev != speedL) phsLr = (1500 + leftTemp);
    if(speedRprev != speedR) phsRr = (1500 - rightTemp);
  }
  */

  etpsL = left;
  etpsR = right;

  //if(!servoCog2) 
  //  servoCog2 = 1 + cogstart(&servos_diffDrive, NULL, servoStack, sizeof(servoStack)-1);

  ssiL = leftTemp;
  ssiR = -rightTemp;

  speedL = left;
  speedR = right;

  if(!cog)
  {
    /////printf("\n\n!!!!! Starting COG !!!!!!\n\n");
    cog = 1 + cogstart(&encoders, NULL, stack, sizeof(stack)-1);
  }  
}


void drive_speed(int left, int right)        // driveSpeeds function
{
  if(!intTabSetup)
  {
    interpolation_table_setup();
    set_drive_speed(0, 0);
    //pause(40);
  }
  
  //
  if(zeroDelay == ON)
  {
    if((speedLprev > 0 && left <= 0) || (speedLprev < 0 && left >= 0) || (speedRprev > 0 && right <= 0) || (speedRprev < 0 && right >= 0))
    {
      int tempLeftZ = left;
      int tempRightZ = right;
      if((speedLprev > 0 && left <= 0) || (speedLprev < 0 && left >= 0))
      {
        tempLeftZ = 0;
      } 
      if((speedRprev > 0 && right <= 0) || (speedRprev < 0 && right >= 0))
      {
        tempRightZ = 0;
      } 
      set_drive_speed(tempLeftZ, tempRightZ);
      speedLprev = tempLeftZ;
      speedRprev = tempRightZ;
      pause(120); 
    }
  }

  //_sprNext = _servoPulseReps;
  //while((_sprNext+1) >= _servoPulseReps);

  set_drive_speed(left, right);

  speedLprev = speedL;
  speedRprev = speedR;
}


void encoders(void *par)
{

  _servoPulseReps = 0;
  int oneshot = 0;

  OUTA &= ~(1 << sPinL); 
  OUTA &= ~(1 << sPinR); 
  DIRA |= 1 << sPinL; 
  DIRA |= 1 << sPinR; 

  pause(20);

  int tempL = 0;
  int tempR = 0;
  interpolate(&tempL, &tempR);  

  PHSA = 0;
  PHSB = 0;
  FRQA = 1;
  FRQB = 1;
  CTRA  = sPinL | (4 << 26);
  CTRB  = sPinR | (4 << 26);
   
  phsL = (1500 + tempL);
  phsR = (1500 - tempR);
  phsLr = phsL;
  phsRr = phsR;

  int t = CNT;
  int dt1 = 13*(CLKFREQ/1000);
  int dt2 = 7*(CLKFREQ/1000);

  phsL = phsLr;
  phsR = phsRr;
  PHSA = -phsL*us;
  PHSB = -phsR*us;
  //waitcnt(t+=dt1);
  //waitcnt(t+=dt);
  _servoPulseReps++;
  //waitcnt(t+=dt2);
  //while(1);
  //t+=(dt1+dt2);
  low(12);
  low(13);

  pause(20);
  PHSA = -phsL*us;
  PHSB = -phsR*us;

  t+=(dt1+dt2);


  int inc = 0;
  int diff = 0;
  int trimAccum = 0;

  int zdirL = 0;
  int zdirR = 0;

  stateL = (INA >> ePinL) & 1;
  stateR = (INA >> ePinR) & 1;

  while(!_servoPulseReps);

  //int dsrL = 400;                                // distance sample rate
  //int dsrR = 394;                                // distance sample rate
  int tdst = CLKFREQ/dsr;                       // time of distance sample
  int td = CNT + tdst;                          // time of distance
  int tdsn = 0;                                 // time of distance sample number
  _sprOld = _servoPulseReps;

  edL = 0;                                      // error distance left
  edR = 0;                                      // error distance right

  pL = 0;                                       // proportional left
  pR = 0;                                       // proportional right

  iL = 0;                                   // integral left
  iR = 0;                                   // integral right

  int maxIR = 0;
  int maxIL = 0;

  while(1)
  {
    // Left encoder
    if(((INA >> ePinL) & 1) != stateL)
    {
      stateL = (~stateL) & 1;
      if(stateL == 1) 
      {
        if((CNT - tiL) > (CLKFREQ/400))
        {
          tiL = CNT;
        }  
      }
      if(phsL > cntrLval + 1500)
      {
        ticksL++;
        zdirL = 1;
      }
      else if(phsL < cntrLval + 1500)
      {
        ticksL--;
        zdirL = -1;
      }
      else
      {
        ticksL += zdirL;
      }
    }
    
    // Right encoder
    if(((INA >> ePinR) & 1) != stateR)
    {
      stateR = (~stateR) & 1;
      if(stateR == 1) 
      {
        if((CNT - tiR) > (CLKFREQ/400))
        {
          tiR = CNT;
        }  
      }
      if(phsR < 1500 - cntrRval)
      {
        ticksR++;
        zdirR = 1;
      }
      else if(phsR > 1500 - cntrRval)
      {
        ticksR--;
        zdirR = -1;
      }
      else
      {
        ticksR += zdirR;
      }
    }

    // Calculated distance accumulator
    if((td - CNT) > tdst) 
    {
  
      td += tdst;                                 // Reset sample timer         '

      dlca += etpsL;                              // + velocityL for dt
      drca += etpsR;                              // + velocityR for dt
      
      //dlca -= 70*(edL - edR);
      
      dlc = dlca/dsr;                             // ticks expected
      drc = drca/dsr;                             

      //#define test_trim_settings_new
      //#ifdef test_trim_settings_new
      if(trimFunction)
      {
        if((((speedL > 0)&&trimFL))||((speedR > 0)&&(trimFR)))
        {
          trimticks = trimticksF;
          dca = dlca*trimFL + drca*trimFR;
        }
        else if((((speedL < 0)&&trimBL))||((speedR < 0)&&(trimBR)))
        {
          trimticks = trimticksB;
          dca = dlca*trimBL + drca*trimBR;
        }
        if((((speedL > 0)&&trimFL))||((speedR > 0)&&(trimFR)))
        {
          if(dca >= trimAccum)
          {
            diff = dca - trimAccum;
            inc = diff/trimticks;
            dca += inc;
            trimAccum += inc;
            trimAccum += (inc*trimticks);         
          }
          dlca += (trimFL*inc);
          drca += (trimFR*inc);
        }
        else if((((speedL < 0)&&trimBL))||((speedR < 0)&&(trimBR)))
        {
          if(dca <= trimAccum)
          {
            diff = dca - trimAccum;
            inc = diff/trimticks;
            dca += inc;
            trimAccum += inc;
            trimAccum += (inc*trimticks);         
          }
          dlca += (trimBL*inc);
          drca += (trimBR*inc);
        }
      }
      //#endif // test_trim_settings_new3
    }
      
    //#define no_control 

    // wait until 15 ms into servo control cycle
    //if(_servoPulseReps != _sprOld)

    /*
    if((CNT - t) >= dt1 && (oneshot == 0))
    {
      oneshot = 1;
      _servoPulseReps++;
    }
    */

    if((CNT - t) >= (dt1 + dt2))
    {
      t+=(dt1+dt2);
      //oneshot = 0;
      //pulseTime = CNT;
      _sprOld = _servoPulseReps;
      pcount++;
      
      // Distance controller
      // #if 1
      if(encoderFeedback)
      {
        edL = dlc - ticksL;
        eaL += edL;
        if(speedL != 0)
        {
          //iL += edL;
          if(speedL > 0)
          {
            pL = edL * (3+(speedL/10));  
            if(edL>0)iL+=1; else if(edL<0) iL-=1;
          }
          else if(speedL < 0)
          {
            pL = edL * (-3+(speedL/10));  
            if(edL>0)iL-=1; else if(edL<0) iL+=1;
          }
          maxIL = speedL;
          if(maxIL < 0) maxIL = -maxIL;
          if(iL > maxIL) iL = maxIL;
          if(iL < -maxIL) iL = -maxIL;
          //iL = 0;
          if(speedL > 0)
            driveL = iL + pL + ssiL + 1500;
            //if(driveL < cntrLval + 1500) driveL = cntrLval + 1500;   
          if(speedL < 0)
            driveL = -iL - pL + ssiL + 1500;
            //if(driveL > cntrLval + 1500) driveL = cntrLval + 1500;   
        }
        else
        {
          driveL = ssiL + 1500;
          iL = 0;
        }
        edR = drc - ticksR;
        eaR += edR;
        if(speedR != 0)
        {
          //iR += edR;
          if(speedR > 0)
          {
            pR = edR * (3+(speedR/10));  
            if(edR>0)iR+=1; else if(edR<0) iR-=1;
          }
          else if(speedR < 0)
          {
            pR = edR * (-3+(speedR/10));  
            if(edR>0)iR-=1; else if(edR<0) iR+=1;
          }
          maxIR = speedR;
          if(maxIR < 0) maxIR = - maxIR;
          if(iR > maxIR) iR = maxIR;
          if(iR < -maxIR) iR = -maxIR;
          //iR = 0;
          if(speedR > 0)
            driveR = -iR - pR + ssiR + 1500;
            //if(driveR > 1500 - cntrRval) driveR = 1500 - cntrRval;
          if(speedR < 0)
            driveR = iR + pR + ssiR + 1500;
            //if(driveR < 1500 - cntrRval) driveR = 1500 - cntrRval;
        }
        else
        {
          driveR = ssiR + 1500;
          iR = 0;
        }
        //#if 1
        //if(encoderFeedback)
        //{
        phsLr = driveL; 
        phsRr = driveR; 
        //}
        //#endif
        // #endif
      }
      else
      {
        phsLr = ssiL + 1500;
        phsRr = ssiR + 1500;
      }

      phsL = phsLr;
      phsR = phsRr;
      PHSA = -phsL*us;
      PHSB = -phsR*us;
      _servoPulseReps++;


      //if(record)
      #ifdef interactive_development_mode
      if(record)
      {
        //rv[ridx] = dlc;
        rv[ridx+0] = speedL;
        rv[ridx+1] = dlc;
        rv[ridx+2] = ticksL;
        rv[ridx+3] = edL;
        rv[ridx+4] = pL;
        rv[ridx+5] = iL;
        //rv[ridx+5] = phsLr;
        rv[ridx+6] = drc;
        rv[ridx+7] = ticksR;
        rv[ridx+8] = edR;
        rv[ridx+9] = pR;
        rv[ridx+10] = iR;
        //rv[ridx+10] = phsRr;
        ridx += 11;
      }
      #endif // interactive_development_mode
    }
  }
}




void drive_record(int startStop)
{
  record = startStop;
}


#ifdef interactive_development_mode
void drive_displayControlSystem(int start, int end)
{
  if(!xbee_setup)
  {
    xbee = fdserial_open(11, 10, 0, 9600);
    xbee_setup = 1;
  }

  dprint(xbee, "\neaL = %d, eaR = %d \n\n", eaL, eaR);
  dprint(xbee, "ridx = %d \n\n", ridx);
  for(int i = start*11; i < (end-1) * 11; i+=11)
  {
    //dprint(xbee, "index = %d, speed = %d, dlc = %d, ticksL = %d, edL = %d, drc = %d, ticksR = %d, edr = %d\n", 
    //      i, rv[i],  rv[i+1], rv[i+2], rv[i+3], rv[i+4], rv[i+5], rv[i+6]); 
    dprint(xbee, "i = %d, v = %d, dlc = %d, ticksL = %d, edL = %d, pL = %d, iL = %d, drc = %d, ticksR = %d, edr = %d, pR = %d, iR = %d\n", 
          i, rv[i],  rv[i+1], rv[i+2], rv[i+3], rv[i+4], rv[i+5], rv[i+6], rv[i+7], rv[i+8], rv[i+9], rv[i+10]); 
  }
  dprint(xbee, "\neaL = %d, eaR = %d \n\n", eaL, eaR);
}
#endif // interactive_development_mode


