/*
  @file control.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


// Angular PID control
int fb360_pidA(int p)
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
  int opMax = fb[p].speedLimit / 4;
  
  if(fb[p].op > opMax) fb[p].op = opMax;
  if(fb[p].op < -opMax) fb[p].op = -opMax;
  
  fb[p].erP = fb[p].er;
  return fb[p].op;
}
  
  
// Velocity PID control
// Calculated distance marches forward based on speed.  The control system 
// calculates position error at 50 Hz by subtracting actual position from 
// calcualted position.  This is the error that is the basis for the 
// P, I, and D calculations.   
int fb360_pidV(int p)  
{
  //while(lockset(lock360));

  int opv;  
  int opMax = fb[p].speedLimit / 4;

  fb[p].speedMeasured = (fb[p].angle - fb[p].angleP) * 50; 
  fb[p].angleDeltaCalc = fb[p].speedTarget / FB360_CS_HZ;
  fb[p].angleCalc += fb[p].angleDeltaCalc;

  fb[p].angleError = fb[p].angleCalc - fb[p].angle;

  fb[p].erDist = fb[p].angleError;
  fb[p].integralV += fb[p].erDist;
  fb[p].derivativeV = fb[p].erDist - fb[p].erDistP;
  
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
int fb360_upsToPulseFromTransferFunction(int unitsPerSec)
{
  int pw, b, mx;
  int ups = unitsPerSec/4;
  
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


void fb360_speedControl(int p)
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
    fb[p].pw = 0;
  }    

  // Acceleration control by taking steps in target speed 
  // toward requested speed
  if(fb[p].speedTarget != fb[p].speedReq)
  {
    int speedDifference = fb[p].speedReq - fb[p].speedTarget;
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
    fb[p].pw = fb360_upsToPulseFromTransferFunction(fb[p].speedTarget);
    fb[p].drive = fb[p].pw - 15000;
    fb[p].opPidV = fb[p].drive + fb360_pidV(p);
  }
  else    
  {
    fb[p].opPidV = fb[p].drive + fb360_pidV(p);
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
  