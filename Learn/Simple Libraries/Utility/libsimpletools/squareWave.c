/**
 * @file squareWave.c
 *
 * @author Andy Lindsay
 *
 * @version dev001
 *
 * @copyright Copyright (C) Parallax, Inc. 2012.  See end of file for
 * terms of use (MIT License).
 *
 * @brief squareWave function source, see simpletools.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */

#include "simpletools.h"

unsigned int stack[(160 + (50*4)) / 4];       // Declare stack space for cog

const unsigned int NCO = (4 << 26);
const unsigned int PLL = (2 << 26);

volatile unsigned int cog;
volatile unsigned int ctr;
volatile unsigned int frq;
volatile int ctrPin;
volatile int sqWaveDt;

void sqWaveCog(void *par);

void squareWave(int pin, int time, int freq)
{
  setupCtr(pin, freq);
  ctrPin = pin;
  sqWaveDt = abs(time) * (CLKFREQ/1000);
  if(time < 0)
  {
    cog = cogstart(&sqWaveCog, NULL,
                   stack, sizeof(stack)) + 1;
    waitcnt(CLKFREQ/5000+CNT);
  }
  else
  {
    sqWaveCog(NULL);
  }
}

int setupCtr(int pin, int freq)
{
  int s;
  int d;
  if(freq < 500000)
  {
    ctr = NCO;
    s = 1;
    d = 0;
  }
  else
  {
    ctr = PLL;
    d = (freq - 1) / 1000000;
    int i;
    for(i = 32; i>0; i--)
    {
      if(d < 0) break;
      d <<= 1;
    }
    d = i;
    s = 4 - d;
    ctr += (d << 23);
  }
  frq = fraction(freq, CLKFREQ, s);
  ctr += pin;
  return ctr;
}

int fraction(int a, int b, int shift)
{
  if (shift > 0)
  {
    a <<= shift;
  }
  if(shift < 0)
  {
    b <<= -shift;
  }
  int f;
  int i;
  for(i = 0; i < 32; i++)
  {
    f <<= 1;
    if(a >= b)
    {
      a -= b;
      f++;
    }
    a <<= 1;
  }
  return f;
}

void sqWaveCog(void *par)
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
  while(CNT - t <= sqWaveDt);
  while(getOutput(ctrPin));
  input(ctrPin);
  if(ctrUsed == 1) CTRA = 0;
  if(ctrUsed == 2) CTRB = 0;
  if(cog)
  {
    cog = 0;
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
