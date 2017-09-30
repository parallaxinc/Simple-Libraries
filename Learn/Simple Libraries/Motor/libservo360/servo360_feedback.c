/*
  @file servo360_feedback.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/



#include "simpletools.h"  
#include "servo360.h"

int servo360_feedback(int pin, int state)
{
  if(!_fb360c.servoCog) servo360_run();
  int p = servo360_findServoIndex(pin);
  if(p == -1)return -1;
  
  if(state == 1 && _fbs[p].feedback == 0)
  {
    /*
    servo360 fbtemp = _fbs[p];
    _fbs[p].pinCtrl = -1;
    _fbs[p].pinFb = -1;
    servo360_connect(fbtemp.pinCtrl, fbtemp.pinFb);
    _fbs[p].unitsRev = _fbs[p].unitsRev;
    _fbs[p].KpV = fbtemp.KpV;
    _fbs[p].KiV = fbtemp.KiV;
    _fbs[p].KdV = fbtemp.KdV;
    _fbs[p].Kp = fbtemp.Kp;
    _fbs[p].Ki = fbtemp.Ki;
    _fbs[p].Kd = fbtemp.Kd;
    _fbs[p].iMax = fbtemp.iMax;
    _fbs[p].iMin = fbtemp.iMin;
    _fbs[p].iMaxV = fbtemp.iMaxV;
    _fbs[p].iMinV = fbtemp.iMinV;
    _fbs[p].speedLimit = fbtemp.speedLimit;
    _fbs[p].rampStep = fbtemp.rampStep;
    //_fbs[p].csop = 0;
    */
    {
      _fbs[p].speedTarget  = 0;
      _fbs[p].angleError = 0;
      _fbs[p].erDist = 0;
      _fbs[p].erDistP = 0;
      _fbs[p].integralV = 0;
      _fbs[p].derivativeV = 0;
      _fbs[p].pV = 0;
      _fbs[p].iV = 0;
      _fbs[p].dV = 0;
      _fbs[p].opPidV = 0;
  
      _fbs[p].angleCalc = _fbs[p].angle;
      //_fbs[p].angleCalcP = _fbs[p].angleCalc;
    }  
    {
      _fbs[p].er = 0;
      _fbs[p].integral = 0;
      _fbs[p].derivative = 0;
      _fbs[p].p = 0;
      _fbs[p].i = 0;
      _fbs[p].d = 0;
      _fbs[p].op = 0;
      _fbs[p].erP = 0;
      _fbs[p].pw = 0;
    }    
      
    //

    //
    servo360_setPositiveDirection(p, S360_CCW_POS);

    _fbs[p].theta = servo360_getTheta(p);  
    _fbs[p].thetaP = _fbs[p].theta;
    _fbs[p].angleFixed = _fbs[p].theta; 
  
    _fbs[p].pvOffset = _fbs[p].angleFixed;
    
    _fbs[p].angle = (_fbs[p].angleSign) * (_fbs[p].angleFixed - _fbs[p].pvOffset);
    _fbs[p].angleCalc = _fbs[p].angle;
    _fbs[p].angleP = _fbs[p].angle;
    _fbs[p].feedback = state;
    //
  }
  else
  {
    //while(lockset(_fb360c.lock360));
    _fbs[p].feedback = state;
    //while(lockset(_fb360c.lock360));
  }    
        

  return p; 
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
