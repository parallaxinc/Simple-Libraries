/*
  @file API_PUBLIC.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
//#include "servo.h" 
#include "fdserial.h"
#include "servo360.h"


int servo360_getAngle(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  

  while(lockset(lock360));
  int val = fb[p].angle;
  val = val * fb[p].unitsRev / UNITS_ENCODER; 
  lockclr(lock360);
  return val;
}  


int fb360_setMaxSpeed(int pin, int speed)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  int retVal = 0;
  
  if(speed <= MAX_SPEED)
  {
    fb[p].speedLimit = speed;
  }    
  else
  {
    retVal -1;
  }    
  return retVal;
}  


int servo360_setMaxSpeed(int pin, int speed)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  speed = speed * UNITS_ENCODER / fb[p].unitsRev;
  int retVal = fb360_setMaxSpeed(pin, speed);
  return retVal;
}


int servo360_speed(int pin, int speed)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  speed = speed * UNITS_ENCODER / fb[p].unitsRev;
  
  while(lockset(lock360));

  if(speed > fb[p].speedLimit)
    fb[p].speedReq = fb[p].speedLimit;
  else if(speed < -fb[p].speedLimit)
    fb[p].speedReq = -fb[p].speedLimit;
  else
    fb[p].speedReq = speed;

  fb[p].csop = SPEED; 

  {
    fb[p].er = 0;
    fb[p].integral = 0;
    fb[p].derivative = 0;
    fb[p].p = 0;
    fb[p].i = 0;
    fb[p].d = 0;
    fb[p].op = 0;
    fb[p].erP = 0;
    fb[p].pw = 0;
  }    
  
  lockclr(lock360);
}  


int servo360_angle(int pin, int position)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  
  fb[p].sp = position * UNITS_ENCODER / fb[p].unitsRev;
  fb[p].csop = POSITION;

  {
    fb[p].speedTarget  = 0;
    fb[p].angleError = 0;
    fb[p].erDist = 0;
    fb[p].erDistP = 0;
    fb[p].integralV = 0;
    fb[p].derivativeV = 0;
    fb[p].pV = 0;
    fb[p].iV = 0;
    fb[p].dV = 0;
    fb[p].opPidV = 0;
  }    
  
  lockclr(lock360);
  
  print("p = %d\r", p);
}  


int servo360_goto(int pin, int position)
{
  int target, offset;
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;


  while(lockset(lock360));

  offset = fb[p].angleTarget;
  target = position * UNITS_ENCODER / fb[0].unitsRev;

  fb[p].angleTarget = target + offset;

  //fb[p].angleTarget = position * UNITS_ENCODER / fb[p].unitsRev;
  fb[p].csop = GOTO;
  lockclr(lock360);
}


int servo360_setUnitsFullCircle(int pin, int units)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  //while(lockset(lock360));
  if(fb[p].unitsRev <= UNITS_FULL_CIRCLE)
  {
    fb[p].unitsRev = units;
    return 0;
  }
  else
  {
    return -1;
  }        
  //lockclr(lock360);
}  


int servo360_connect(int pinControl, int pinFeedback)
{
  if(!servoCog) fb360_run();

  if(fb360_findServoIndex(pinControl) != -1)
    return -4;
    
  if(fb360_findServoIndex(pinFeedback) != -1)
    return -5;
    
  if(pinControl >= 28 && pinFeedback >= 28)
    return -6;

  if(devCount >= FB360_DEVS_MAX)
    return -7;

  while(lockset(lock360));

  int result = -1;
  /*
  for(int p = 0; p < FB360_DEVS_MAX; p++) 
  {
    print("fb[%d].pinCtrl = %d, fb[%d].pinFb = %d\r", p, fb[p].pinCtrl, p, fb[p].pinFb);
  }
  */
  for(int p = 0; p < FB360_DEVS_MAX; p++) 
  {
    //print("fb[%d].pinCtrl = %d, fb[%d].pinFb = %d\r", p, fb[p].pinCtrl, p, fb[p].pinFb);
    if( (fb[p].pinCtrl == -1) && (fb[p].pinFb == -1) )
    {
      //fb[p].pinCtrl = pinControl;
      //fb[p].pinFb = pinFeedback;
      result = p;
      break;
    //print("\r");
    }
  }
  //lockclr(lock360);

  int p = result;
  
  fb[p].speedReq = 0;
  fb[p].pinCtrl = pinControl;
  fb[p].pinFb = pinFeedback;
  
  fb[p].unitsRev = UNITS_REV;
  
  fb[p].KpV = KPV;
  fb[p].KiV = KIV;
  fb[p].KdV = KDV;
  
  fb[p].Kp = KPA;
  fb[p].Ki = KIA;
  fb[p].Kd = KDA;
  
  fb[p].pw = PW_CENTER;
  fb[p].iMax = FB360_POS_INTGRL_MAX;
  fb[p].iMin = FB360_POS_INTGRL_MAX;
  
  fb[p].speedLimit = MAX_SPEED;
  fb[p].rampStep = FB360_RAMP_STEP;
  
  //while(lockset(lock360));
 
  fb360_setPositiveDirection(p, CCW_POS);

  fb[p].theta = fb360_getTheta(p);  
  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixed = fb[p].theta; 

  //fb360_captureOffset(p);
  fb[p].pvOffset = fb[p].angleFixed;
  
  fb[p].angle = (fb[p].angleSign) * (fb[p].angleFixed - fb[p].pvOffset);
  fb[p].angleCalc = fb[p].angle;
  fb[p].angleP = fb[p].angle;

  devCount++;

  lockclr(lock360);  
  print("devCount: %d, index: %d, p: %d\r", devCount, result, p); 
  print("fb[%d].pinCtrl = %d, fb[%d].pinFb = %d\r", p, fb[p].pinCtrl, p, fb[p].pinFb);


  return result;
}


int servo360_setAcceleration(int pin, int unitsPerSecSquared)               
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  //int rampStep = unitsPerSecSquared * 

  fb360_setRampStep(pin, unitsPerSecSquared * UNITS_ENCODER 
                         / (FB360_CS_HZ * fb[p].unitsRev));  
}

int servo360_get(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].angle;
  lockclr(lock360);
  return val;
}                    


int servo360_getAngleFixedOrigin(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].theta;
  lockclr(lock360);
  return val;
}  

int servo360_enable(int pin, int state)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  int index = fb360_findServoIndex(pin);
  while(lockset(lock360));
  //enable = state;
  while(lockset(lock360));
  return index; 
}

int servo360_stop(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  int index = fb360_findServoIndex(pin);
  while(lockset(lock360));
  //servo_speed(pin, 0);
  while(lockset(lock360));
  return index; 
}

int servo360_feedback(int pin, int state)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  int index = fb360_findServoIndex(pin);
  while(lockset(lock360));
  fb[p].feedback = state;
  while(lockset(lock360));
  return index; 
}


int servo360_set(int pinControl, int time)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pinControl);
  if(p == -1)return -1;

  servo360_feedback(pinControl, 0);
  //pulseControl(pinControl, time - 1500);
}  


int servo360_setAngleLimits(int pin, int ccwMax, int cwMax)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  int index = fb360_findServoIndex(pin);
  while(lockset(lock360));
  fb[p].angleMax = ccwMax;
  fb[p].angleMin = cwMax;
  while(lockset(lock360));
  return index; 
}


int fb360_checkDistanceRemaining(int pin, int speed, int finalAngle)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
}


/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
