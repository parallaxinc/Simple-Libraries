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
  if(!servoCog) servo360_run();
  int p = servo360_findServoIndex(pin);
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
    servo360_setPositiveDirection(p, CCW_POS);

    fb[p].theta = servo360_getTheta(p);  
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
