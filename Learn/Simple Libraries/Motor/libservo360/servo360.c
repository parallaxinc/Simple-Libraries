#include "simpletools.h"  
//#include "servo.h" 
//#include "fdserial.h"
#include "servo360.h"

                           ////// ALL SERVOS //////

//extern fdserial *term;
int *servoCog;
volatile int lock360;
volatile int devCount;
static volatile int t360;
static volatile int dt360;
volatile int angleSign = CCW_POS;
volatile int cntPrev;

servo360 fb[2];


void fb360_run(void)
{
  servoCog = cog_run(fb360_mainLoop, 512); 
  cntPrev = CNT;
  pause(500);
}
  
void fb360_end(void)
{
  lockret(lock360);
  cog_end(servoCog);
} 


void fb360_servoPulse(int p)
{
  //high(26);
  int pin = fb[p].pinCtrl;
  low(pin);
  //low(12);
  PHSA = 0;
  FRQA = 0;
  CTRA = (4 << 26) | pin;
  FRQA = 1;
  PHSA = -(15000 + fb[p].speedOut) * (CLKFREQ/10000000);
  //low(26);
  /*
  low(27);
  PHSB = 0;
  FRQB = 0;
  CTRB = (4 << 26) | 27;
  FRQB = 1;
  PHSB = -(15000 + 500) * (CLKFREQ/10000000);
  */
  while(get_state(pin));
  CTRA = 0;
  PHSA = 0;
  FRQA = 0;
}   


void fb360_mainLoop()
{
  fb360_setup();
  
  //low(27);
  
  //int p = 0;

  while(1)
  {
    waitcnt(t360 += dt360);
    for(int p = 0; p < devCount; p+= 1)
    //if(devCount > 0)
    {
      //toggle(27);
      fb360_checkAngle(p);
      fb360_outputSelector(p);
      //fb[p].speedOut = 0;
      fb360_servoPulse(p);
      //toggle(27);
    }      
  }    
}  


void fb360_setup(void)
{
  
  for(int p = 0; p < FB360_DEVS_MAX; p++)
  {
    fb[p].pinCtrl = -1;
    fb[p].pinFb = -1;
  } 
  
  devCount = 0;   
  
  lock360 = locknew();
  lockclr(lock360);
  
  dt360 = CLKFREQ/50;
  t360  = CNT + dt360;
}  


void fb360_waitServoCtrllEdgeNeg(int p)
{
  int mask = 1 << fb[p].pinCtrl;
  if(!(INA & mask))
  { 
    while(!(INA & mask));
  }
  while(INA & mask);
}      


void fb360_checkAngle(int p)
{
  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixedP = fb[p].angleFixed;
  fb[p].angleP = fb[p].angle;  
  fb[p].dcp = fb[p].dc;
  
  fb[p].theta = fb360_getTheta(p);  
  
  fb[p].turns += fb360_crossing(fb[p].theta, fb[p].thetaP, UNITS_ENCODER);

  if(fb[p].turns >= 0)
  {
    fb[p].angleFixed = (fb[p].turns * UNITS_ENCODER) + fb[p].theta;
  }      
  else if(fb[p].turns < 0)
  {
    fb[p].angleFixed = (UNITS_ENCODER * (fb[p].turns + 1)) + (fb[p].theta - UNITS_ENCODER);
  }

  fb[p].angle = fb[p].angleFixed - fb[p].pvOffset;
}  
 

void fb360_outputSelector(int p)
{
  if(fb[p].csop == POSITION)
  {
    int output = fb360_pidA(p);
    fb[p].pw = fb360_upsToPulseFromTransferFunction(output);
    fb[p].speedOut = fb[p].pw - 15000;
  }
  else if(fb[p].csop == SPEED)
  {
    fb360_speedControl(p);
    fb[p].speedOut = fb[p].opPidV;
  }   
  else if(fb[p].csop == GOTO)
  {
    fb[p].ticksDiff = fb[p].angleTarget - fb[p].angle;
    fb[p].ticksGuard = ( fb[p].speedReq * abs(fb[p].speedReq) ) / (110 * fb[p].rampStep);
    //ticksGuard = ticksGuard * UNITS_ENCODER / unitsRev;
    if((fb[p].ticksDiff < 0) && (fb[p].ticksDiff < fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      fb[p].speedReq = -fb[p].speedLimit;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff > fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      fb[p].speedReq = fb[p].speedLimit;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff <= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq -= rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    }    
    else if((fb[p].ticksDiff < 0) && (fb[p].ticksDiff >= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq += rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    } 
    else
    {
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    }       
    if
    ( 
      (abs(fb[p].ticksDiff) < (fb[p].rampStep / (fb[p].unitsRev * 50))) 
      || (fb[p].approachFlag == 1 && fb[p].speedMeasured == 0)
    )
    {
      fb[p].speedReq = 0;
      fb[p].speedTarget = 0;
      fb[p].sp = fb[p].angleTarget;
      fb[p].csop = POSITION;
      fb[p].approachFlag = 0;
      //return;
    }      
  }
  else if(fb[p].csop == MONITOR)
  {
    
  } 
}                  




