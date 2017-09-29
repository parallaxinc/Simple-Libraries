/*
  @file servo360_connect.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"

int servo360_connect(int pinControl, int pinFeedback)
{

  int t1 = pulse_in(pinFeedback, 1);
  if( (t1 > 1200) || (t1 < 25) ) return -8;

  if(!servoCog) servo360_run();

  if(servo360_findServoIndex(pinControl) != -1)
    return -4;
    
  if(servo360_findServoIndex(pinFeedback) != -1)
    return -5;
    
  if(pinControl >= 28 && pinFeedback >= 28)
    return -6;

  if(devCount >= S360_DEVS_MAX)
    return -7;

  while(lockset(lock360));

  int result = -1;

  for(int p = 0; p < S360_DEVS_MAX; p++) 
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
  
  fb[p].unitsRev = S360_UNITS_REV;
  
  fb[p].KpV = KPV;
  fb[p].KiV = KIV;
  fb[p].KdV = KDV;
  fb[p].iMax = S360_POS_INTGRL_MAX;
  fb[p].iMin = -S360_POS_INTGRL_MAX;
  
  fb[p].Kp = KPA;
  fb[p].Ki = KIA;
  fb[p].Kd = KDA;
  fb[p].iMaxV = S360_VEL_INTGRL_MAX;
  fb[p].iMinV = -S360_VEL_INTGRL_MAX;
  
  fb[p].pw = S360_PW_CENTER;
  
  fb[p].speedLimit = S360_MAX_SPEED;
  fb[p].rampStep = S360_RAMP_STEP;
  
  servo360_setPositiveDirection(p, S360_CCW_POS);

  fb[p].theta = servo360_getTheta(p);  
  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixed = fb[p].theta; 

  fb[p].pvOffset = fb[p].angleFixed;
  
  fb[p].angle = (fb[p].angleSign) * (fb[p].angleFixed - fb[p].pvOffset);
  fb[p].angleCalc = fb[p].angle;
  fb[p].angleP = fb[p].angle;
  
  fb[p].angleMax = S360_A_MAX;
  fb[p].angleMin = -S360_A_MAX;
  
  fb[p].opMax = S360_MAX_SPEED;

  fb[p].couple = 0;
  fb[p].coupleScale = 0;
  
  fb[p].feedback = 1;

  devCount++;
  
  lockclr(lock360);  

  return result;
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
