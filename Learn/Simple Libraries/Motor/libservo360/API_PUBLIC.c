/*
  @file API_PUBLIC.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


int servo360_getTurns(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  return fb[p].turns;
}  


int servo360_setTurns(int pin, int turns)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  int delta = turns * FB360_ENC_RES;
  
  while(lockset(lock360));
  
  fb[p].angle += delta;  
  fb[p].angleP += delta;
  fb[p].angleFixed += delta;
  fb[p].angleFixedP += delta;
  fb[p].turns += turns;


  if(fb[p].csop == POSITION)
  {
    fb[p].sp += delta;
    fb[p].angleTarget += delta;
  }
  //
  else if(fb[p].csop == SPEED)
  {
    fb[p].angleCalc += delta;
    fb[p].angleTarget += delta;
  }
  //
  else if(fb[p].csop == GOTO)
  {
    fb[p].angleTarget += delta;
    fb[p].sp += delta;
    fb[p].angleCalc += delta;
  }    
  
  lockclr(lock360);
  
  return 0;
}   


int servo360_setControlSys(int pin, int constant, int value)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  switch(constant)
  {
    case S360_KPV:
      fb[p].KpV = value;
      break;
    case S360_KIV:
      fb[p].KiV = value;
      break;
    case S360_KDV:
      fb[p].KdV = value;
      break;
    case S360_IV_MAX:
      fb[p].iMaxV = value;
      fb[p].iMinV = -value;
      break;
    case S360_KPA:
      fb[p].Kp = value;
      break;
    case S360_KIA:
      fb[p].Ki = value;
      break;
    case S360_KDA:
      fb[p].Kd = value;
      break;
    case S360_IA_MAX:
      fb[p].iMax = value;
      fb[p].iMin = -value;
      break;
  }  
}    


int servo360_getControlSys(int pin, int constant)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  int value; 
  
  switch(constant)
  {
    case S360_KPV:
      value = fb[p].KpV;
      break;
    case S360_KIV:
      value = fb[p].KiV;
      break;
    case S360_KDV:
      value = fb[p].KdV;
      break;
    case S360_IV_MAX:
      value = fb[p].iMaxV;
      break;
    case S360_KPA:
      value = fb[p].Kp;
      break;
    case S360_KIA:
      value = fb[p].Ki;
      break;
    case S360_KDA:
      value = fb[p].Kd;
      break;
    case S360_IA_MAX:
      value = fb[p].iMax;
      break;
  }  
  return value;
}    


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


int servo360_getMaxSpeed(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  return (fb[p].speedLimit * fb[p].unitsRev) / UNITS_ENCODER;
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
  //fb360_waitServoCtrllEdgeNeg(devCount - 1);
}  


int servo360_getSpeed(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  return fb[p].speedMeasured * fb[p].unitsRev / FB360_ENC_RES;
}  


int servo360_angle(int pin, int position)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  if(position >= fb[p].angleMax) position = fb[p].angleMax;
  if(position <= fb[p].angleMin) position = fb[p].angleMin;

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
}  


int servo360_goto(int pin, int position)
{
  int target, offset;
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));

  offset = fb[p].angleTarget;
  target = position * UNITS_ENCODER / fb[p].unitsRev;

  fb[p].angleTarget = target + offset;

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


int servo360_getUnitsFullCircle(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  return fb[p].unitsRev;
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

  for(int p = 0; p < FB360_DEVS_MAX; p++) 
  {
    if( (fb[p].pinCtrl == -1) && (fb[p].pinFb == -1) )
    {
      result = p;
      break;
    }
  }

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
  fb[p].iMin = -FB360_POS_INTGRL_MAX;
  fb[p].iMaxV = FB360_VEL_INTGRL_MAX;
  fb[p].iMinV = -FB360_VEL_INTGRL_MAX;
  
  fb[p].speedLimit = MAX_SPEED;
  fb[p].rampStep = FB360_RAMP_STEP;
  
  fb360_setPositiveDirection(p, CCW_POS);

  fb[p].theta = fb360_getTheta(p);  
  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixed = fb[p].theta; 

  fb[p].pvOffset = fb[p].angleFixed;
  
  fb[p].angle = (fb[p].angleSign) * (fb[p].angleFixed - fb[p].pvOffset);
  fb[p].angleCalc = fb[p].angle;
  fb[p].angleP = fb[p].angle;
  
  fb[p].angleMax = S360_A_MAX;
  fb[p].angleMin = -S360_A_MAX;
  
  fb[p].feedback = 1;

  devCount++;
  
  lockclr(lock360);  

  return result;
}


int servo360_setAcceleration(int pin, int unitsPerSecSquared)               
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  fb360_setRampStep(pin, unitsPerSecSquared * UNITS_ENCODER 
                         / (FB360_CS_HZ * fb[p].unitsRev));  
}


int servo360_setRampStep(int pin, int stepSize)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  fb360_setRampStep(pin, stepSize);  
  return p;
}  

int servo360_getAcceleration(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1) return -1;
  
  int acceleration = servo360_getRampStep(pin);
  acceleration *= (FB360_CS_HZ * fb[p].unitsRev);
  acceleration /= UNITS_ENCODER;
  return acceleration;
}


int servo360_getAngle12Bit(int pin)
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
  if(p == -1) return -1;

  //while(lockset(lock360));
  servo360_speed(pin, 0);
  //while(lockset(lock360));
  return p; 
}


int servo360_feedback(int pin, int state)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
  
  if(state == 1 && fb[p].feedback == 0)
  {
    /*
    servo360 fbtemp = fb[p];
    fb[p].pinCtrl = -1;
    fb[p].pinFb = -1;
    servo360_connect(fbtemp.pinCtrl, fbtemp.pinFb);
    fb[p].unitsRev = fb[p].unitsRev;
    fb[p].KpV = fbtemp.KpV;
    fb[p].KiV = fbtemp.KiV;
    fb[p].KdV = fbtemp.KdV;
    fb[p].Kp = fbtemp.Kp;
    fb[p].Ki = fbtemp.Ki;
    fb[p].Kd = fbtemp.Kd;
    fb[p].iMax = fbtemp.iMax;
    fb[p].iMin = fbtemp.iMin;
    fb[p].iMaxV = fbtemp.iMaxV;
    fb[p].iMinV = fbtemp.iMinV;
    fb[p].speedLimit = fbtemp.speedLimit;
    fb[p].rampStep = fbtemp.rampStep;
    //fb[p].csop = 0;
    */
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
  
      fb[p].angleCalc = fb[p].angle;
      //fb[p].angleCalcP = fb[p].angleCalc;
    }  
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
      
    //

    //
    fb360_setPositiveDirection(p, CCW_POS);

    fb[p].theta = fb360_getTheta(p);  
    fb[p].thetaP = fb[p].theta;
    fb[p].angleFixed = fb[p].theta; 
  
    fb[p].pvOffset = fb[p].angleFixed;
    
    fb[p].angle = (fb[p].angleSign) * (fb[p].angleFixed - fb[p].pvOffset);
    fb[p].angleCalc = fb[p].angle;
    fb[p].angleP = fb[p].angle;
    fb[p].feedback = state;
    //
  }
  else
  {
    //while(lockset(lock360));
    fb[p].feedback = state;
    //while(lockset(lock360));
  }    
        

  return p; 
}


int servo360_set(int pinControl, int time)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pinControl);
  if(p == -1)return -1;

  //servo360_feedback(pinControl, 0);
  fb[p].speedOut = (time - 1500) * 10;
  
  return p;
}  


int servo360_setAngleLimits(int pin, int ccwMax, int cwMax)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  //while(lockset(lock360));
  fb[p].angleMax = ccwMax;
  fb[p].angleMin = cwMax;
  //while(lockset(lock360));
  return p; 
}


int servo360_getAngleLimits(int pin, int *ccwMax, int *cwMax)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  //while(lockset(lock360));
  *ccwMax = fb[p].angleMax;
  *cwMax = fb[p].angleMin;
  //while(lockset(lock360));
  return p; 
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
