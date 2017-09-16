#include "abdrive360.h"


//                                            //                                //  


static volatile int initialized = 0;

static volatile int unitsPerRev = ABD360_UNITS_REV;

static volatile int pinCtrlLeft = ABD60_PIN_CTRL_L;
static volatile int pinCtrlRight = ABD360_PIN_CTRL_R;
static volatile int pinFbLeft = ABD60_PIN_FB_L;
static volatile int pinFbRight = ABD360_PIN_FB_R;

static volatile int speedLimit = ABD_SPEED_LIMIT;
static volatile int rampStep = ABD_RAMP_STEP;
static volatile int speedLimitGoto = ABD_GOTO_SPEED_LIMIT;
static volatile int rampStepGoto = ABD_GOTO_RAMP_STEP;

static volatile int gotoMode = ABD360_GOTO_BLOCK;


void drive_init(void)
{
  servo360_connect(pinCtrlLeft, pinFbLeft);
  servo360_connect(pinCtrlRight, pinFbRight);

  servo360_setUnitsFullCircle(pinCtrlLeft, ABD360_UNITS_REV);
  servo360_setUnitsFullCircle(pinCtrlRight, ABD360_UNITS_REV);

  servo360_setAcceleration(pinCtrlLeft, rampStep * 50);
  servo360_setAcceleration(pinCtrlRight, rampStep * 50);

  servo360_setMaxSpeed(pinCtrlLeft, speedLimit);
  servo360_setMaxSpeed(pinCtrlRight, speedLimit);

  initialized = 1;
}  


void drive_speed(int left, int right)
{
  if(!initialized) drive_init();

  servo360_speed(pinCtrlLeft, left);
  servo360_speed(pinCtrlRight, -right);
}   


void drive_getTicks(int *left, int *right)
{
  if(!initialized) drive_init();

  *left = servo360_getAngle(pinCtrlLeft);
  *right = servo360_getAngle(pinCtrlRight);
}  

//void drive_calibrationResults(void);

void drive_getTicksCalc(int *left, int *right)
{
  if(!initialized) drive_init();

  *left = servo360_getAngleCalc(pinCtrlLeft);
  *right = servo360_getAngleCalc(pinCtrlRight);
}  


// Different, returns 
int drive_gotoStatus(int side)
{
  if(!initialized) drive_init();

  int statusLeft = 0, statusRight = 0;
  
  if(side == SIDE_LEFT || side == SIDE_BOTH) 
  {
    statusLeft = (servo360_getCsop(pinCtrlLeft) == 3);
  }  
  if(side == SIDE_RIGHT || side == SIDE_BOTH) 
  {
    statusRight = (servo360_getCsop(pinCtrlRight) == 3);
  }  
  
  return statusLeft + statusRight;
}


// Importrant, must call before anything that controls motion.
// (...as in before the cog is launched.  We are assuming users do 
// not intend to hot-swap their ActivityBot connections!)
void drive_servoPins(int servoPinLeft, int servoPinRight)
{
  pinCtrlLeft = servoPinLeft;
  pinCtrlRight = servoPinRight;
} 

// Comment same as for drive_servoPins.
void drive_encoderPins(int encPinLeft, int encPinRight)
{
  pinFbLeft = encPinLeft;
  pinFbRight = encPinRight;
}  


// Probably doesn't work 
void drive_feedback(int enabled)
{
  if(!initialized) drive_init();

  servo360_feedback(pinCtrlLeft, enabled);
  servo360_feedback(pinCtrlRight, enabled);
} 

// ABD360_GOTO_BLOCK 0
// ABD360_GOTO_SET_FORGET 1
void drive_gotoMode(int mode)
{
  if(!initialized) drive_init();

  gotoMode = mode;
} 
  
void drive_setAcceleration(int forGotoOrSpeed, int ticksPerSecSq)
{
  if(!initialized) drive_init();

  if(forGotoOrSpeed == FOR_SPEED)
  {
    rampStep = ticksPerSecSq / 50;
    servo360_setAcceleration(pinCtrlLeft, ticksPerSecSq);
    servo360_setAcceleration(pinCtrlRight, ticksPerSecSq);
  }
  else if(forGotoOrSpeed == FOR_SPEED)
  {
    rampStepGoto = ticksPerSecSq;
  }    
} 
  
/* depricate
void drive_setErrorLimit(int maxDistDiffTicks);
{
  
} 
*/  

void drive_setMaxVelocity(int forGotoOrSpeed, int ticksPerSec)
{
  if(!initialized) drive_init();

  if(forGotoOrSpeed == FOR_SPEED)
  {
    speedLimit = ticksPerSec;
    servo360_setMaxSpeed(pinCtrlLeft, ticksPerSec);
    servo360_setMaxSpeed(pinCtrlRight, ticksPerSec);
  }
  else if(forGotoOrSpeed == FOR_SPEED)
  {
    speedLimitGoto = ticksPerSec;
  }    
} 
  
  
void drive360_unitsPerRev(int units)
{
  if(!initialized) drive_init();

  servo360_setUnitsFullCircle(pinCtrlLeft, units);
  servo360_setUnitsFullCircle(pinCtrlRight, units);
} 
  
  
void drive_goto(int distLeft, int distRight)
{
  /*
  #ifdef _console_
    dprint(term, "\r\rdrive_goto(%d, %d)\r\r", distLeft, distRight);
  #endif  
  */

  int rampStepTemp, speedMaxTemp, 
      ratio, slowerSide,
      rampStepEnc, speedLimitEnc;
  
  if(!initialized) drive_init();
  
  servo360_setAcceleration(pinCtrlLeft, rampStepGoto * 50);
  servo360_setAcceleration(pinCtrlRight, rampStepGoto * 50);
  servo360_setMaxSpeed(pinCtrlLeft, speedLimitGoto);
  servo360_setMaxSpeed(pinCtrlRight, speedLimitGoto);

  if(abs(distRight) > abs(distLeft))
  {
    rampStepEnc = servo360_getRampStep(pinCtrlLeft);
    speedLimitEnc = servo360_getTopSpeed(pinCtrlLeft);

    ratio = 1000 * abs(distLeft) / abs(distRight);
    
    rampStepTemp = rampStepEnc * ratio / 1000;
    speedMaxTemp = speedLimitEnc * ratio / 1000;
    
    fb360_setRampStep(pinCtrlLeft, rampStepTemp); 
    fb360_setMaxSpeed(pinCtrlLeft, speedMaxTemp);
    
    slowerSide = AB360_LEFT;
  }
  else if(abs(distLeft) > abs(distRight))
  {
    rampStepEnc = servo360_getRampStep(pinCtrlRight);
    speedLimitEnc = servo360_getTopSpeed(pinCtrlRight);

    ratio = 1000 * abs(distRight) / abs(distLeft);
    
    rampStepTemp = rampStepEnc * ratio / 1000;
    speedMaxTemp = speedLimitEnc * ratio / 1000;
    
    fb360_setMaxSpeed(pinCtrlRight, speedMaxTemp);
    fb360_setRampStep(pinCtrlRight, rampStepTemp); 
    
    slowerSide = AB360_RIGHT;
  }
  else
  {
    slowerSide = AB360_NEITHER;
  }
  
  servo360_goto(pinCtrlLeft, distLeft);
  servo360_goto(pinCtrlRight, -distRight);
  
  while(servo360_getCsop(pinCtrlLeft) == GOTO && servo360_getCsop(pinCtrlRight) == GOTO);
  
  servo360_setAcceleration(pinCtrlLeft, rampStep * 50);
  servo360_setAcceleration(pinCtrlRight, rampStep * 50);
  servo360_setMaxSpeed(pinCtrlLeft, speedLimit);
  servo360_setMaxSpeed(pinCtrlRight, speedLimit);
  
  pause(1000);
}  


void drive_setRampStep(int stepsize)
{
  if(!initialized) drive_init();

  servo360_setAcceleration(pinCtrlLeft, stepsize * 50);
  servo360_setAcceleration(pinCtrlRight, stepsize * 50);
}

void drive_ramp(int left, int right)
{
  drive_speed(left, right);
}


void drive_rampStep(int left, int right)
{
  drive_speed(left, right);
}



/*
void drive_init(void)
{
  servo360_connect(pinCtrlLeft, pinFbLeft);
  servo360_connect(pinCtrlRight, pinFbRight);

  servo360_setUnitsFullCircle(pinCtrlLeft, 64);
  servo360_setUnitsFullCircle(pinCtrlRight, 64);
  //dprint(term, "\r\rfb[0].unitsRev = %d, ", fb[0].unitsRev);
  //dprint(term, "fb[1].unitsRev = %d\r\r", fb[1].unitsRev);

  //fb360_setRampStep(pinCtrlLeft, 768); 
  //fb360_setRampStep(pinCtrlRight, 768); 
  servo360_setAcceleration(pinCtrlLeft, rampStep * 50);
  servo360_setAcceleration(pinCtrlRight, rampStep * 50);
  //dprint(term, "\r\rfb[0].rampStep = %d, ", fb[0].rampStep);
  //dprint(term, "fb[1].rampStep = %d\r\r", fb[1].rampStep);
  
  //fb360_setMaxSpeed(pinCtrlLeft, 4096 * 2);
  //fb360_setMaxSpeed(pinCtrlRight, 4096 * 2);
  servo360_setMaxSpeed(pinCtrlLeft, speedLimit);
  servo360_setMaxSpeed(pinCtrlRight, speedLimit);
  //dprint(term, "\r\rfb[0].speedMax = %d, ", fb[0].speedLimit);
  //dprint(term, "fb[1].speedMax = %d\r\r", fb[1].speedLimit);
  
  initialized = 1;
}  
*/

