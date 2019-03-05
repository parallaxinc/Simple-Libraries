/*
  @file pwm2ch.c
 
  @author Andy Lindsay
 
  @version 0.5
 
  @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
  terms of use (MIT License).
 
  @brief pwm2ch function source, see pwm2ch.h for documentation.
 
  @detail Please submit bug reports, suggestions, and improvements to
  this code to editor@parallax.com.
*/

#include "simpletools.h"
#include "pwm2ch.h"

#ifndef NCO_PWM_1
#define NCO_PWM_1 0b00100 << 26
#endif

void pwm2chDriver(void *par);

pwm2ch *pwm2ch_start(unsigned int cycleMicroseconds)
{
  pwm2ch *device;
  device = (void *) malloc(sizeof(pwm2ch));
  //device->tCycle = cycleMicroseconds * st_usTicks;
  device->tCycle = cycleMicroseconds * (CLKFREQ / 1000000);
  device->ctra = 0;
  device->ctrb = 0;
  device->pwm2cog = cogstart(pwm2chDriver, device, device->pwm2stack, sizeof(device->pwm2stack)) + 1;  
  return device;
}

void pwm2ch_set(pwm2ch *device, int pin, int channel, int tHigh)
{
  if(!channel)
  {
    int temp = NCO_PWM_1;
    temp |= pin;
    device->ctra = temp;
    device->ticksA = tHigh * st_usTicks;
    if(tHigh < 0)
    {
      device->ctra = 0;
    }      
  }
  else
  {
    int temp = NCO_PWM_1;
    temp |= pin;
    device->ctrb = temp;
    device->ticksB = tHigh * st_usTicks;
    if(tHigh < 0)
    {
      device->ctrb = 0;
    }      
  }
}

void pwm2ch_stop(pwm2ch *device)
{
  if(device->pwm2cog) cogstop(device->pwm2cog - 1);  
  device->pwm2cog = 0;
  free(device);
}

void pwm2chDriver(void *par)
{
  pwm2ch *device = (pwm2ch *) par;
  FRQA = 1;
  FRQB = 1;
  //int pin;
  unsigned int dt = device->tCycle;
  unsigned int t = CNT;
  while(1)
  {
    waitcnt(t+=dt);
    //int temp = CTRA;
    if(device->ctra != CTRA)
    {
      if(CTRA != 0)
      {
        device->pin = CTRA & 0b111111;
        DIRA &= ~(1 << device->pin);
      }
      CTRA = device->ctra;
      if(device->ctra != 0)
      {
        device->pin = CTRA & 0b111111;      
        DIRA |= (1 << device->pin);
      }        
    }
    //temp = CTRB;
    if(device->ctrb != CTRB)
    {
      if(CTRB != 0)
      {
        device->pin = CTRB & 0b111111;
        DIRA &= ~(1 << device->pin);
      }
      CTRB = device->ctrb;
      if(device->ctrb != 0)
      {
        device->pin = CTRB & 0b111111;      
        DIRA |= (1 << device->pin);
      }        
    }
    PHSA = -device->ticksA;    
    PHSB = -device->ticksB;
    //    
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
