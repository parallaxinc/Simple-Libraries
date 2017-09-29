/*
  @file servo360.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


#define couple_servos


int *servoCog;
volatile int lock360;
volatile int devCount;
volatile int t360;
volatile int t360slice;
volatile int dt360;
volatile int angleSign = CCW_POS;
volatile int cntPrev;
volatile int dt360a[2];
volatile int pulseCount;

servo360_t fb[servo360_DEVS_MAX];


void servo360_run(void)
{
  servoCog = cog_run(servo360_mainLoop, 512); 
  cntPrev = CNT;
  pause(500);
}

  
void servo360_end(void)
{
  lockret(lock360);
  cog_end(servoCog);
} 


void servo360_setup(void)
{
  for(int p = 0; p < servo360_DEVS_MAX; p++)
  {
    fb[p].pinCtrl = -1;
    fb[p].pinFb = -1;
  } 
  
  devCount = 0;   
  
  lock360 = locknew();
  lockclr(lock360);
  
  dt360 = CLKFREQ / servo360_FREQ_CTRL_SIG;  // 20 ms
  t360  = CNT;
  dt360a[0] = 16 * (CLKFREQ / 1000);      // 16 ms
  dt360a[1] = 18 * (CLKFREQ / 1000);      // 18 ms
}


void servo360_mainLoop()
{
  servo360_setup();
  
  while(1)
  {
    //while((CNT - t360) < dt360);
    //while((CNT - t360) < dt360);
    

    for(int p = 0; p < servo360_DEVS_MAX; p++)
    {
      if(fb[p].pinCtrl != -1 && fb[p].pinFb != -1)
      {
        if(fb[p].feedback)
        {
          servo360_checkAngle(p);
        }          
      }        
    }
    
    while(lockset(lock360));
    for(int p = 0; p < servo360_DEVS_MAX; p++)
    {
      if(fb[p].pinCtrl != -1 && fb[p].pinFb != -1)
      {
        if(fb[p].feedback)
        {
          if(fb[p].dc != -1)
            servo360_outputSelector(p);
        }          
      }        
    }

    #ifdef couple_servos

    for(int p = 0; p < servo360_DEVS_MAX; p++)
    {
      if((fb[p].couple != -1) && (fb[p].feedback))
      {
        if(fb[p].speedTarget > 0) fb[p].stepDir = 1;
        else if(fb[p].speedTarget < 0) fb[p].stepDir = -1;
        else  fb[p].stepDir = 0;
    
        fb[p].lag = fb[p].stepDir * fb[p].angleError;
      
        if(fb[fb[p].couple].speedTarget > 0) fb[fb[p].couple].stepDir = 1;
        else if(fb[fb[p].couple].speedTarget < 0) fb[fb[p].couple].stepDir = -1;
        else  fb[fb[p].couple].stepDir = 0;
    
        fb[fb[p].couple].lag = fb[fb[p].couple].stepDir * fb[fb[p].couple].angleError;
    
        if(fb[fb[p].couple].lag > fb[p].lag)
        {
          int compensate = fb[fb[p].couple].lag - fb[p].lag;
          compensate = fb[p].coupleScale * compensate / S360_SCALE_DEN_COUPLE;
          if(compensate > 500) compensate = 500;           
    
          if(fb[p].speedOut > 0) fb[p].speedOut -= compensate;
          if(fb[p].speedOut < 0) fb[p].speedOut += compensate;
        }
        else if(fb[p].lag > fb[fb[p].couple].lag)
        {
          int compensate = fb[p].lag - fb[fb[p].couple].lag;
          compensate = fb[p].coupleScale * compensate / S360_SCALE_DEN_COUPLE;
          if(compensate > 500) compensate = 500;           
      
          if(fb[fb[p].couple].speedOut > 0) fb[fb[p].couple].speedOut -= compensate;
          if(fb[fb[p].couple].speedOut < 0) fb[fb[p].couple].speedOut += compensate;
        }
      }        
    }

    #endif
    
    lockclr(lock360);
    
    int target[2];
    target[0] = t360 + dt360a[0];
    target[1] = t360 + dt360a[1];

    for(int p = 0; p < servo360_DEVS_MAX; p++)
    {
      if(p % 2 == 1)
      {
        //while((CNT - t360) <  dt360a[p/2]);
        waitcnt(target[p/2]);
        servo360_servoPulse(p - 1, p);
      }        
    }      

    t360 += dt360;
  }    
}  


void servo360_servoPulse(int p, int q)
{
  pulseCount++;
  int pinA = fb[p].pinCtrl;
  int pinB = fb[q].pinCtrl;

  if(pinA != -1 && fb[p].dc != -1)
  {
    low(pinA);
    PHSA = 0;
    FRQA = 0;
    CTRA = (4 << 26) | pinA;
    FRQA = 1;
    PHSA = -(15000 + fb[p].speedOut) * (CLKFREQ/10000000);
  }   

  if(pinB != -1 && fb[q].dc != -1)
  {
    low(pinB);
    PHSB = 0;
    FRQB = 0;
    CTRB = (4 << 26) | pinB;
    FRQB = 1;
    PHSB = -(15000 + fb[q].speedOut) * (CLKFREQ/10000000);
  }    

  if(pinA != -1 && fb[p].dc != -1)
  {
    while(get_state(pinA));
    CTRA = 0;
    PHSA = 0;
    FRQA = 0;
  }    
  
  if(pinB != -1 && fb[q].dc != -1)
  {
    while(get_state(pinB));
    CTRB = 0;
    PHSB = 0;
    FRQB = 0;
  }    
}   
//


void servo360_waitServoCtrllEdgeNeg(int p)
{
  int mask = 1 << fb[p].pinCtrl;
  if(!(INA & mask))
  { 
    while(!(INA & mask));
  }
  while(INA & mask);
}      


void servo360_checkAngle(int p)
{

  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixedP = fb[p].angleFixed;
  fb[p].angleP = fb[p].angle;  
  fb[p].dcp = fb[p].dc;
  
  fb[p].theta = servo360_getTheta(p);  
  
  fb[p].turns += servo360_crossing(fb[p].theta, fb[p].thetaP, UNITS_ENCODER);

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
 

void servo360_outputSelector(int p)
{
  if(fb[p].csop == POSITION)
  {
    int output = servo360_pidA(p);
    fb[p].pw = servo360_upsToPulseFromTransferFunction(output);
    fb[p].speedOut = fb[p].pw - 15000;
  }
  else if(fb[p].csop == SPEED)
  {
    servo360_speedControl(p);
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
      //servo360_speedControl(p);
      //fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff > fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      fb[p].speedReq = fb[p].speedLimit;
      //servo360_speedControl(p);
      //fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff <= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq -= rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      //servo360_speedControl(p);
      //fb[p].speedOut = fb[p].opPidV;
    }    
    else if((fb[p].ticksDiff < 0) && (fb[p].ticksDiff >= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq += rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      //servo360_speedControl(p);
      //fb[p].speedOut = fb[p].opPidV;
    } 
    else
    {
      //servo360_speedControl(p);
      //fb[p].speedOut = fb[p].opPidV;
    }       
    
    servo360_speedControl(p);
    fb[p].speedOut = fb[p].opPidV;
    
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


int servo360_dutyCycle(int p, int scale)
{
  int t = CNT;
  int dt = 3 * (CLKFREQ/1000);
  
  int pin = fb[p].pinFb;
  CTRA = (1000 << 26) | pin;
  CTRB = (1100 << 26) | pin;
  FRQA = 1;
  FRQB = 1;
  
  int mask = 1 << pin;
  int phsa, phsb;
  
  while(INA & mask) if(CNT - t > dt) break;
  PHSA = 0;
  while(!(INA & mask)) if(CNT - t > dt) break;
  PHSB = 0;
  while(INA & mask) if(CNT - t > dt) break;
  phsa = PHSA;
  while(!(INA & mask)) if(CNT - t > dt) break;
  phsb = PHSB;
  
  CTRA = 0;
  CTRB = 0;

  int dc = (phsa * scale) / (phsa + phsb);
  
  if(CNT - t > dt)
  {
    return -1;
  }
  else
  {    
    return dc;
  }    
}  


int servo360_getTheta(int p)
{
  fb[p].dc = servo360_dutyCycle(p, servo360_M); 
  
  if(fb[p].angleSign == CCW_POS)
  {
    fb[p].theta = (servo360_ENC_RES - 1) - (fb[p].dc + servo360_B);
  }
  else if(fb[p].angleSign == CCW_NEG)
  {    
    fb[p].theta = fb[p].dc + servo360_B;
  }  

  fb[p].theta &= 0xFFF;
  return fb[p].theta;
}  


int servo360_crossing(int current, int previous, int units)
{
  int angleLow = units/3;
  int angleHigh = angleLow * 2;
  if(previous > angleHigh && current < angleLow)
  {
    return 1;
  }    
  else if(previous < angleLow && current > angleHigh)
  {
    return -1;
  }    
  else
  {
    return 0;
  }    
}      


void servo360_setPositiveDirection(int p, int direction)
{
  fb[p].angleSign = direction;
}  


// Angular PID control
int servo360_pidA(int p)
{
  // Clear any speed control system corrections so that return to speed control
  // doesn't start with unexpected compensation.
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
  
  // Angle error
  fb[p].er = fb[p].sp - fb[p].angle;
  // Integral accumuliation
  fb[p].integral += fb[p].er;
  // Derivative difference
  fb[p].derivative = fb[p].er - fb[p].erP;
  
  // Clamp itegral level
  if(fb[p].integral > fb[p].iMax) fb[p].integral = fb[p].iMax;
  if(fb[p].integral < fb[p].iMin) fb[p].integral = fb[p].iMin;

  // Calculate influences of P, I, and D.
  fb[p].p = (fb[p].Kp * fb[p].er) / SCALE_DEN_A;
  fb[p].i = (fb[p].Ki * fb[p].integral) / SCALE_DEN_A;
  fb[p].d = (fb[p].Kd * fb[p].derivative) / SCALE_DEN_A;
  
  // Output = sum(P, I, and D)
  fb[p].op = (fb[p].p + fb[p].i + fb[p].d);
  
  // Limit output proportional to speed limit???  This may have been intended
  // to be proportional to the current target speed.
  //int opMax = fb[p].speedLimit / 4;
  //int opMax = fb[p].speedLimit;
  
  if(fb[p].op > fb[p].opMax) fb[p].op = fb[p].opMax;
  if(fb[p].op < -fb[p].opMax) fb[p].op = -fb[p].opMax;
  
  fb[p].erP = fb[p].er;
  return fb[p].op;
}
  
  
// Velocity PID control
// Calculated distance marches forward based on speed.  The control system 
// calculates position error at 50 Hz by subtracting actual position from 
// calcualted position.  This is the error that is the basis for the 
// P, I, and D calculations.   
int servo360_pidV(int p)  
{
  //while(lockset(lock360));

  //int opv;  
  int opMax = fb[p].speedLimit;

  fb[p].speedMeasured = (fb[p].angle - fb[p].angleP) * 50; 
  if(abs(fb[p].angleError) < UNITS_ENCODER/4)
  {
    fb[p].angleDeltaCalc = fb[p].speedTarget / servo360_CS_HZ;
    fb[p].angleCalc += fb[p].angleDeltaCalc;
  }    

  fb[p].angleError = fb[p].angleCalc - fb[p].angle;

  if(abs(fb[p].angleError) < UNITS_ENCODER/4)
  {
    fb[p].erDist = fb[p].angleError;
    fb[p].integralV += fb[p].erDist;
    fb[p].derivativeV = fb[p].erDist - fb[p].erDistP;
  }    
  
  if(fb[p].integralV > fb[p].iMaxV) fb[p].integralV = fb[p].iMaxV;
  if(fb[p].integralV < fb[p].iMinV) fb[p].integralV = fb[p].iMinV;

  fb[p].pV = (fb[p].KpV * fb[p].erDist) / SCALE_DEN_V;
  fb[p].iV = (fb[p].KiV * fb[p].integralV) / SCALE_DEN_V;
  fb[p].dV = (fb[p].KdV * fb[p].derivativeV) / SCALE_DEN_V;
  
  fb[p].opV = fb[p].pV + fb[p].iV + fb[p].dV;

  if(fb[p].opV > opMax) fb[p].opV = opMax;
  if(fb[p].opV < -opMax) fb[p].opV = -opMax;
  
  fb[p].erDistP = fb[p].erDist;
  
  //lockclr(lock360);  

  return fb[p].opV;
}


// Select pulse width from graph of angular velocity vs. pulse width
// for the servo.  This is done once for each new speed.  After the pulse
// is delivered once, the control system adjusts upward or downward from
// that initial value.
int servo360_upsToPulseFromTransferFunction(int unitsPerSec)
{
  int pw, b, mx;
  int ups = unitsPerSec/7;
  
  if(ups > 0)
  {
    mx = ups;
    b = B_POS;
    pw = mx + b;
  }
  else if(ups < 0)
  {
    mx = ups;
    b = B_NEG;
    pw = mx + b;
  }    
  else
  {
    pw = 15000;
  }
  return pw;    
}  


void servo360_speedControl(int p)
{
  // If we switch back to position control, it doesn't
  // work well to have old settings error correction from
  // the last time position was controlled, so clear the
  // settings.
  {
    fb[p].er = 0;
    fb[p].integral = 0;
    fb[p].derivative = 0;
    fb[p].p = 0;
    fb[p].i = 0;
    fb[p].d = 0;
    fb[p].op = 0;
    fb[p].erP = 0;
    //fb[p].pw = 0;
  }    

  // Acceleration control by taking steps in target speed 
  // toward requested speed
  if(fb[p].speedTarget != fb[p].speedReq)
  {
    int speedDifference = fb[p].speedReq - fb[p].speedTarget;
    if(abs(fb[p].angleError) < UNITS_ENCODER/4)
    {
      if( abs(speedDifference) > fb[p].rampStep)
      {
        if(speedDifference > 0)
        {
          fb[p].speedTarget += fb[p].rampStep;
        }
        else if(speedDifference < 0)
        {
          fb[p].speedTarget -= fb[p].rampStep;
        }        
      }
      else
      {
        fb[p].speedTarget = fb[p].speedReq;
        //speedUpdateFlag = 0;
      }
    }      
    fb[p].pw = servo360_upsToPulseFromTransferFunction(fb[p].speedTarget);
    fb[p].drive = fb[p].pw - 15000;
    fb[p].opPidV = fb[p].drive + servo360_pidV(p);
  }
  else    
  {
    fb[p].opPidV = fb[p].drive + servo360_pidV(p);
  }
  fb[p].speedTargetP = fb[p].speedTarget;
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
