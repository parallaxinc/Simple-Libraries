/**
 * @file dac.c
 *
 * @author Andy Lindsay
 *
 * @version dev001
 *
 * @copyright Copyright (C) Parallax, Inc. 2012.  See end of file for
 * terms of use (MIT License).
 *
 * @brief dac function source, see simpletools.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */

#include "simpletools.h"

unsigned int stack[(160 + (50*4)) / 4];       // Declare stack space for cog

const unsigned int DUTY_SE = (6 << 26);

volatile unsigned int cog;
volatile unsigned int ctr;
volatile unsigned int frq;
volatile int ctrPin;
volatile int dacDt;
volatile int dacBit = 1 << (32 - 8);

void dacCog(void *par);

void dac(int pin, int time, int dacVal)
{
  ctr = DUTY_SE + pin;
  ctrPin = pin;
  dacDt = abs(time) * (CLKFREQ/1000);
  frq = dacVal * dacBit;
  //cog = cogstart(&dacCog, NULL, stack, sizeof(stack));
  if(time < 0)
  {
    cog = cogstart(&dacCog, NULL, stack, sizeof(stack)) + 1;
    waitcnt(CLKFREQ/5000+CNT);
  }
  else
  {
    dacCog(NULL);
  }
}

void dacCog(void *par)
{
  int t;
  int ctrUsed = 0;
  low(ctrPin);
  t = CNT;
  if(CTRA == 0)                               // If CTRA unused
  {
    FRQA = frq;                               // FRQA increments PHSA by 1
    CTRA = ctr;                               // Configure CTRA
    ctrUsed = 1;
  }
  else if(CTRB == 0)                          // If CTRA used, try CTRB
  {
    CTRB = ctr;                               // Configure CTRA
    FRQB = frq;                               // FRQA increments PHSA by 1
    ctrUsed = 2;
  }
  while(CNT - t <= dacDt);
  input(ctrPin);
  if(ctrUsed == 1) CTRA = 0;
  if(ctrUsed == 2) CTRB = 0;
  //cogstop(cogid());
  if(cog)
  {
    cog = 0;
    low(ctrPin);
    input(ctrPin);
    cogstop(cogid());
  }
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
