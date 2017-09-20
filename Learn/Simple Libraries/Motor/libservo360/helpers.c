/*
  @file helpers.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


int servo360_getAngleCalc(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].angleCalc;
  lockclr(lock360);
  return val;
}  

int servo360_getCsop(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].csop;
  lockclr(lock360);
  return val;
}  


int servo360_getTopSpeed(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].speedLimit;
  lockclr(lock360);
  return val;
}  


int servo360_getRampStep(int pin)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;

  while(lockset(lock360));
  int val = fb[p].rampStep;
  lockclr(lock360);
  return val;
}  


int fb360_setRampStep(int pin, int stepSize)
{
  if(!servoCog) fb360_run();
  int p = fb360_findServoIndex(pin);
  if(p == -1)return -1;
    
  while(lockset(lock360));
  fb[p].rampStep = stepSize;
  lockclr(lock360);
}


int fb360_findServoIndex(int pin)
{
  int p = 0;
  while(1)
  {
    //print("p = %d, ", p);
    if(p >= (FB360_DEVS_MAX))
    {
      return -1;
    }       
    if(fb[p].pinCtrl == pin || fb[p].pinFb == pin)
    {
      return p;
    }
    p++;
  }          
}  


void fb360_captureOffset(int p)
{
  fb[p].pvOffset = fb[p].angleFixed;
}  


int unitsAngleToEncoder(int value)
{
  int result = value * UNITS_ENCODER / fb[0].unitsRev;
  return result;
}  


int unitsEncoderToAngle(int value)
{
  int result = value * fb[0].unitsRev / UNITS_ENCODER;
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
