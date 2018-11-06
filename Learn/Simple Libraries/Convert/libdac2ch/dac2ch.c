/*
  @file dac2ch.c
 
  @author Andy Lindsay
 
  @version 0.5
 
  @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
  terms of use (MIT License).
 
  @brief dac2ch function source, see dac2ch.h for documentation.
 
  @detail Please submit bug reports, suggestions, and improvements to
  this code to editor@parallax.com.
*/

#include "simpletools.h"
#include "dac2ch.h"

#ifndef DUTY_SE
#define DUTY_SE (0b110 << 26)
#endif

void dac2chDriver(void *par);

dac2ch *dac2ch_start(int bits)
{
  dac2ch *device;
  device = (void *) malloc(sizeof(dac2ch));
  device->dacCtrBits = bits;
  device->dacBitX = 32 - device->dacCtrBits;
  device->ctra = 0;
  device->ctrb = 0;
  device->dac2chCog = cogstart(dac2chDriver, device, device->dac2chStack, sizeof(device->dac2chStack)) + 1;  
  return device;
}

void dac2ch_stop(dac2ch *device)
{
  if(device->dac2chCog) cogstop(device->dac2chCog - 1);  
  device->dac2chCog = 0;
  free(device);
}

void dac2ch_set(dac2ch *device, int pin, int channel, int dacVal)
{
  int temp = DUTY_SE;
  temp |= pin;

  if(!channel)
  {
    if(dacVal >= 0)
    {
      device->ctra = temp;
      device->frqa = (dacVal << device->dacBitX);
    }      
    else 
    {
      device->ctra = 0;
      device->frqa = 0;
    }      
  }
  else
  {
    if(dacVal >= 0)
    {
      device->ctrb = temp;
      device->frqb = (dacVal << device->dacBitX);
    }      
    else 
    {
      device->ctrb = 0;
      device->frqb = 0;
    }      
  }    
}

void dac2chDriver(void *par)
{
  dac2ch *device = (dac2ch *) par;
  FRQA = 1;
  FRQB = 1;
  while(1)
  {
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
    
    FRQA = device->frqa;    
    FRQB = device->frqb;
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
