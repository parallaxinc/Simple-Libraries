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

  if(!_fb360c.servoCog) servo360_run();

  if(servo360_findServoIndex(pinControl) != -1)
    return -4;
    
  if(servo360_findServoIndex(pinFeedback) != -1)
    return -5;
    
  if(pinControl >= 28 && pinFeedback >= 28)
    return -6;

  if(_fb360c.devCount >= S360_DEVS_MAX)
    return -7;

  while(lockset(_fb360c.lock360));

  int result = -1;

  for(int p = 0; p < S360_DEVS_MAX; p++) 
  {
    if( (_fbs[p].pinCtrl == -1) && (_fbs[p].pinFb == -1) )
    {
      result = p;
      break;
    }
  }

  int p = result;
  
  _fbs[p].speedReq = 0;
  _fbs[p].pinCtrl = pinControl;
  _fbs[p].pinFb = pinFeedback;
  
  _fbs[p].unitsRev = S360_UNITS_REV;
  
  _fbs[p].KpV = S360_KPV;
  _fbs[p].KiV = S360_KIV;
  _fbs[p].KdV = S360_KDV;
  _fbs[p].iMax = S360_POS_INTGRL_MAX;
  _fbs[p].iMin = -S360_POS_INTGRL_MAX;
  
  _fbs[p].Kp = S360_KPA;
  _fbs[p].Ki = S360_KIA;
  _fbs[p].Kd = S360_KDA;
  _fbs[p].iMaxV = S360_VEL_INTGRL_MAX;
  _fbs[p].iMinV = -S360_VEL_INTGRL_MAX;
  
  _fbs[p].pw = S360_PW_CENTER;
  
  _fbs[p].speedLimit = S360_MAX_SPEED;
  _fbs[p].rampStep = S360_RAMP_STEP;
  
  servo360_setPositiveDirection(p, S360_CCW_POS);

  _fbs[p].theta = servo360_getTheta(p);  
  _fbs[p].thetaP = _fbs[p].theta;
  _fbs[p].angleFixed = _fbs[p].theta; 

  _fbs[p].pvOffset = _fbs[p].angleFixed;
  
  _fbs[p].angle = (_fbs[p].angleSign) * (_fbs[p].angleFixed - _fbs[p].pvOffset);
  _fbs[p].angleCalc = _fbs[p].angle;
  _fbs[p].angleP = _fbs[p].angle;
  
  _fbs[p].angleMax = S360_A_MAX;
  _fbs[p].angleMin = -S360_A_MAX;
  
  _fbs[p].opMax = S360_MAX_SPEED;

  _fbs[p].couple = 0;
  _fbs[p].coupleScale = 0;
  
  _fbs[p].feedback = 1;

  _fb360c.devCount++;
  
  lockclr(_fb360c.lock360);  

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
