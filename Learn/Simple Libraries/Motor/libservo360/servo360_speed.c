/*
  @file servo360_speed.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


int servo360_speed(int pin, int speed)
{
  if(!_fb360c.servoCog) servo360_run();
  int p = servo360_findServoIndex(pin);
  if(p == -1)return -1;
  
  speed = speed * S360_UNITS_ENCODER / _fbs[p].unitsRev;
  
  if(speed != _fbs[p].speedReq)
  {
    while(lockset(_fb360c.lock360));
  
    if(speed > _fbs[p].speedLimit)
      _fbs[p].speedReq = _fbs[p].speedLimit;
    else if(speed < -_fbs[p].speedLimit)
      _fbs[p].speedReq = -_fbs[p].speedLimit;
    else
      _fbs[p].speedReq = speed;
  
    _fbs[p].csop = S360_SPEED; 
    lockclr(_fb360c.lock360);
  
    {
      _fbs[p].er = 0;
      _fbs[p].integral = 0;
      _fbs[p].derivative = 0;
      _fbs[p].p = 0;
      _fbs[p].i = 0;
      _fbs[p].d = 0;
      _fbs[p].op = 0;
      _fbs[p].erP = 0;
      //_fbs[p].pw = 0;
    }    
    
  }    
  //servo360_waitServoCtrllEdgeNeg(_fb360c.devCount - 1);
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
