/*
  @file encoder.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"

//servo360 fb[2];

int fb360_dutyCycle(int p, int scale)
{
  int pin = fb[p].pinFb;
  CTRA = (1000 << 26) | pin;
  CTRB = (1100 << 26) | pin;
  FRQA = 1;
  FRQB = 1;
  
  int mask = 1 << pin;
  int phsa, phsb;
  
  while(INA & mask);
  PHSA = 0;
  while(!(INA & mask));
  PHSB = 0;
  while(INA & mask);
  phsa = PHSA;
  while(!(INA & mask));
  phsb = PHSB;
  
  CTRA = 0;
  CTRB = 0;

  int dc = (phsa * scale) / (phsa + phsb);
  
  return dc;
}  


int fb360_getTheta(int p)
{
  fb[p].dc = fb360_dutyCycle(p, FB360_M); 
  
  if(fb[p].angleSign == CCW_POS)
  {
    fb[p].theta = (FB360_ENC_RES - 1) - (fb[p].dc + FB360_B);
  }
  else if(fb[p].angleSign == CCW_NEG)
  {    
    fb[p].theta = fb[p].dc + FB360_B;
  }  

  fb[p].theta &= 0xFFF;
  return fb[p].theta;
}  


int fb360_crossing(int current, int previous, int units)
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


void fb360_setPositiveDirection(int p, int direction)
{
  fb[p].angleSign = direction;
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
