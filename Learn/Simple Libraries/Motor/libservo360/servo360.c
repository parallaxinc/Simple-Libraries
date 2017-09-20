/*
  @file servo360.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"

                           ////// ALL SERVOS //////

//extern fdserial *term;
int *servoCog;
volatile int lock360;
volatile int devCount;
volatile int t360;
volatile int t360slice;
volatile int dt360;
volatile int angleSign = CCW_POS;
volatile int cntPrev;
volatile int dt360fbSlice;
volatile int dt360spSlice;

servo360 fb[FB360_DEVS_MAX];


void fb360_run(void)
{
  servoCog = cog_run(fb360_mainLoop, 512); 
  cntPrev = CNT;
  pause(500);
}

  
void fb360_end(void)
{
  lockret(lock360);
  cog_end(servoCog);
} 


void fb360_setup(void)
{
  for(int p = 0; p < FB360_DEVS_MAX; p++)
  {
    fb[p].pinCtrl = -1;
    fb[p].pinFb = -1;
  } 
  
  devCount = 0;   
  
  lock360 = locknew();
  lockclr(lock360);
  
  dt360 = CLKFREQ / FB360_FREQ_CTRL_SIG;  // 20 ms
  dt360fbSlice = 4 * dt360 / 5;           // 16 ms
  dt360spSlice = dt360 / 10;              // 2 ms
  t360  = CNT;
  t360slice = t360;
}


void fb360_mainLoop()
{
  fb360_setup();
  
  while(1)
  {
    //waitcnt(t360 += dt360);
    t360 += dt360;
    while(CNT - t360 < dt360);
    for(int p = 0; p < FB360_DEVS_MAX; p++)
    {
      if(fb[p].pinCtrl != -1 && fb[p].pinFb != -1)
      {
        fb360_checkAngle(p);
        fb360_outputSelector(p);
      }        
    }      
    for(int p = 0; p < FB360_DEVS_MAX; p++)
    {
      if(p % 2 == 1)
      {
        //waitcnt(t360 + dt360fbSlice + ((p/2) * (dt360spSlice)));
        int timeInc = dt360fbSlice + ((p/2) * (dt360spSlice));
        while(CNT - t360 <  timeInc);
        fb360_servoPulse(p - 1, p);
      }        
    }      
  }    
}  
//


//
void fb360_servoPulse(int p, int q)
{
  int pinA = fb[p].pinCtrl;
  int pinB = fb[q].pinCtrl;

  if(pinA != -1)
  {
    low(pinA);
    PHSA = 0;
    FRQA = 0;
    CTRA = (4 << 26) | pinA;
    FRQA = 1;
    PHSA = -(15000 + fb[p].speedOut) * (CLKFREQ/10000000);
  }   

  //if(pinB != -1 && q < FB360_DEVS_MAX)
  if(pinB != -1)
  {
    low(pinB);
    PHSB = 0;
    FRQB = 0;
    CTRB = (4 << 26) | pinB;
    FRQB = 1;
    PHSB = -(15000 + fb[q].speedOut) * (CLKFREQ/10000000);
  }    

  if(pinA != -1)
  {
    while(get_state(pinA));
    CTRA = 0;
    PHSA = 0;
    FRQA = 0;
  }    
  
  //if(pinB != -1 && q < FB360_DEVS_MAX)
  if(pinB != -1)
  {
    while(get_state(pinB));
    CTRB = 0;
    PHSB = 0;
    FRQB = 0;
  }    
}   
//




void fb360_waitServoCtrllEdgeNeg(int p)
{
  int mask = 1 << fb[p].pinCtrl;
  if(!(INA & mask))
  { 
    while(!(INA & mask));
  }
  while(INA & mask);
}      


void fb360_checkAngle(int p)
{
  fb[p].thetaP = fb[p].theta;
  fb[p].angleFixedP = fb[p].angleFixed;
  fb[p].angleP = fb[p].angle;  
  fb[p].dcp = fb[p].dc;
  
  fb[p].theta = fb360_getTheta(p);  
  
  fb[p].turns += fb360_crossing(fb[p].theta, fb[p].thetaP, UNITS_ENCODER);

  if(fb[p].turns >= 0)
  {
    fb[p].angleFixed = (fb[p].turns * UNITS_ENCODER) + fb[p].theta;
  }      
  else if(fb[p].turns < 0)
  {
    fb[p].angleFixed = (UNITS_ENCODER * (fb[p].turns + 1)) + (fb[p].theta - UNITS_ENCODER);
  }

  fb[p].angle = fb[p].angleFixed - fb[p].pvOffset;
}  
 

void fb360_outputSelector(int p)
{
  if(fb[p].csop == POSITION)
  {
    int output = fb360_pidA(p);
    fb[p].pw = fb360_upsToPulseFromTransferFunction(output);
    fb[p].speedOut = fb[p].pw - 15000;
  }
  else if(fb[p].csop == SPEED)
  {
    fb360_speedControl(p);
    fb[p].speedOut = fb[p].opPidV;
  }   
  else if(fb[p].csop == GOTO)
  {
    fb[p].ticksDiff = fb[p].angleTarget - fb[p].angle;
    fb[p].ticksGuard = ( fb[p].speedReq * abs(fb[p].speedReq) ) / (110 * fb[p].rampStep);
    //ticksGuard = ticksGuard * UNITS_ENCODER / unitsRev;
    if((fb[p].ticksDiff < 0) && (fb[p].ticksDiff < fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      fb[p].speedReq = -fb[p].speedLimit;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff > fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      fb[p].speedReq = fb[p].speedLimit;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
      fb[p].approachFlag = 0;
    }
    else if((fb[p].ticksDiff > 0) && (fb[p].ticksDiff <= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq -= rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    }    
    else if((fb[p].ticksDiff < 0) && (fb[p].ticksDiff >= fb[p].ticksGuard) && (fb[p].approachFlag == 0))
    {
      //speedReq += rampStep;
      fb[p].speedReq = 0;
      fb[p].approachFlag = 1;
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    } 
    else
    {
      fb360_speedControl(p);
      fb[p].speedOut = fb[p].opPidV;
    }       
    if
    ( 
      (abs(fb[p].ticksDiff) < (fb[p].rampStep / (fb[p].unitsRev * 50))) 
      || (fb[p].approachFlag == 1 && fb[p].speedMeasured == 0)
    )
    {
      fb[p].speedReq = 0;
      fb[p].speedTarget = 0;
      fb[p].sp = fb[p].angleTarget;
      fb[p].csop = POSITION;
      fb[p].approachFlag = 0;
      //return;
    }      
  }
  else if(fb[p].csop == MONITOR)
  {
    
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
