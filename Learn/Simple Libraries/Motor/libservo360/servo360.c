/*
  @file servo360.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


#define couple_servos

/*
int *servoCog;
volatile int _fb360c.lock360;
volatile int _fb360c.devCount;
volatile int _fb360c.t360;
volatile int _fb360c.t360slice;
volatile int _fb360c.dt360;
volatile int angleSign = S360_CCW_POS;
volatile int _fb360c.cntPrev;
volatile int dt360a[2];
volatile int _fb360c.pulseCount;
*/


servo360_cog_t _fb360c;
servo360_t _fbs[S360_DEVS_MAX];


void servo360_run(void)
{
  _fb360c.servoCog = cog_run(servo360_mainLoop, 512); 
  _fb360c.cntPrev = CNT;
  pause(500);
}

  
void servo360_end(void)
{
  lockret(_fb360c.lock360);
  cog_end(_fb360c.servoCog);
} 


void servo360_setup(void)
{
  for(int p = 0; p < S360_DEVS_MAX; p++)
  {
    _fbs[p].pinCtrl = -1;
    _fbs[p].pinFb = -1;
  } 
  
  _fb360c.devCount = 0;   
  
  _fb360c.lock360 = locknew();
  lockclr(_fb360c.lock360);
  
  _fb360c.dt360 = CLKFREQ / S360_FREQ_CTRL_SIG;  // 20 ms
  _fb360c.t360  = CNT;
  _fb360c.dt360a[0] = 16 * (CLKFREQ / 1000);      // 16 ms
  _fb360c.dt360a[1] = 18 * (CLKFREQ / 1000);      // 18 ms
}


void servo360_mainLoop()
{
  servo360_setup();
  
  while(1)
  {
    //while((CNT - _fb360c.t360) < _fb360c.dt360);
    //while((CNT - _fb360c.t360) < _fb360c.dt360);
    

    for(int p = 0; p < S360_DEVS_MAX; p++)
    {
      if(_fbs[p].pinCtrl != -1 && _fbs[p].pinFb != -1)
      {
        if(_fbs[p].feedback)
        {
          servo360_checkAngle(p);
        }          
      }        
    }
    
    while(lockset(_fb360c.lock360));
    for(int p = 0; p < S360_DEVS_MAX; p++)
    {
      if(_fbs[p].pinCtrl != -1 && _fbs[p].pinFb != -1)
      {
        if(_fbs[p].feedback)
        {
          if(_fbs[p].dc != -1)
            servo360_outputSelector(p);
        }          
      }        
    }

    #ifdef couple_servos

    for(int p = 0; p < S360_DEVS_MAX; p++)
    {
      if((_fbs[p].couple != -1) && (_fbs[p].feedback))
      {
        if(_fbs[p].speedTarget > 0) _fbs[p].stepDir = 1;
        else if(_fbs[p].speedTarget < 0) _fbs[p].stepDir = -1;
        else  _fbs[p].stepDir = 0;
    
        _fbs[p].lag = _fbs[p].stepDir * _fbs[p].angleError;
      
        if(_fbs[_fbs[p].couple].speedTarget > 0) _fbs[_fbs[p].couple].stepDir = 1;
        else if(_fbs[_fbs[p].couple].speedTarget < 0) _fbs[_fbs[p].couple].stepDir = -1;
        else  _fbs[_fbs[p].couple].stepDir = 0;
    
        _fbs[_fbs[p].couple].lag = _fbs[_fbs[p].couple].stepDir * _fbs[_fbs[p].couple].angleError;
    
        if(_fbs[_fbs[p].couple].lag > _fbs[p].lag)
        {
          int compensate = _fbs[_fbs[p].couple].lag - _fbs[p].lag;
          compensate = _fbs[p].coupleScale * compensate / S360_SCALE_DEN_COUPLE;
          if(compensate > 500) compensate = 500;           
    
          if(_fbs[p].speedOut > 0) _fbs[p].speedOut -= compensate;
          if(_fbs[p].speedOut < 0) _fbs[p].speedOut += compensate;
        }
        else if(_fbs[p].lag > _fbs[_fbs[p].couple].lag)
        {
          int compensate = _fbs[p].lag - _fbs[_fbs[p].couple].lag;
          compensate = _fbs[p].coupleScale * compensate / S360_SCALE_DEN_COUPLE;
          if(compensate > 500) compensate = 500;           
      
          if(_fbs[_fbs[p].couple].speedOut > 0) _fbs[_fbs[p].couple].speedOut -= compensate;
          if(_fbs[_fbs[p].couple].speedOut < 0) _fbs[_fbs[p].couple].speedOut += compensate;
        }
      }        
    }

    #endif
    
    lockclr(_fb360c.lock360);
    
    int target[2];
    target[0] = _fb360c.t360 + _fb360c.dt360a[0];
    target[1] = _fb360c.t360 + _fb360c.dt360a[1];

    for(int p = 0; p < S360_DEVS_MAX; p++)
    {
      if(p % 2 == 1)
      {
        //while((CNT - _fb360c.t360) <  dt360a[p/2]);
        waitcnt(target[p/2]);
        servo360_servoPulse(p - 1, p);
      }        
    }      

    _fb360c.t360 += _fb360c.dt360;
  }    
}  


void servo360_servoPulse(int p, int q)
{
  _fb360c.pulseCount++;
  int pinA = _fbs[p].pinCtrl;
  int pinB = _fbs[q].pinCtrl;

  if(pinA != -1 && _fbs[p].dc != -1)
  {
    low(pinA);
    PHSA = 0;
    FRQA = 0;
    CTRA = (4 << 26) | pinA;
    FRQA = 1;
    PHSA = -(15000 + _fbs[p].speedOut) * (CLKFREQ/10000000);
  }   

  if(pinB != -1 && _fbs[q].dc != -1)
  {
    low(pinB);
    PHSB = 0;
    FRQB = 0;
    CTRB = (4 << 26) | pinB;
    FRQB = 1;
    PHSB = -(15000 + _fbs[q].speedOut) * (CLKFREQ/10000000);
  }    

  if(pinA != -1 && _fbs[p].dc != -1)
  {
    while(get_state(pinA));
    CTRA = 0;
    PHSA = 0;
    FRQA = 0;
  }    
  
  if(pinB != -1 && _fbs[q].dc != -1)
  {
    while(get_state(pinB));
    CTRB = 0;
    PHSB = 0;
    FRQB = 0;
  }    
}   
//


void servo360_waitServoCtrllEdgeNeg(int p)
{
  int mask = 1 << _fbs[p].pinCtrl;
  if(!(INA & mask))
  { 
    while(!(INA & mask));
  }
  while(INA & mask);
}      


void servo360_checkAngle(int p)
{

  _fbs[p].thetaP = _fbs[p].theta;
  _fbs[p].angleFixedP = _fbs[p].angleFixed;
  _fbs[p].angleP = _fbs[p].angle;  
  _fbs[p].dcp = _fbs[p].dc;
  
  _fbs[p].theta = servo360_getTheta(p);  
  
  _fbs[p].turns += servo360_crossing(_fbs[p].theta, _fbs[p].thetaP, S360_UNITS_ENCODER);

  if(_fbs[p].turns >= 0)
  {
    _fbs[p].angleFixed = (_fbs[p].turns * S360_UNITS_ENCODER) + _fbs[p].theta;
  }      
  else if(_fbs[p].turns < 0)
  {
    _fbs[p].angleFixed = (S360_UNITS_ENCODER * (_fbs[p].turns + 1)) + (_fbs[p].theta - S360_UNITS_ENCODER);
  }

  _fbs[p].angle = _fbs[p].angleFixed - _fbs[p].pvOffset;
}  
 

void servo360_outputSelector(int p)
{
  if(_fbs[p].csop == S360_POSITION)
  {
    int output = servo360_pidA(p);
    _fbs[p].pw = servo360_upsToPulseFromTransferFunction(output);
    _fbs[p].speedOut = _fbs[p].pw - 15000;
  }
  else if(_fbs[p].csop == S360_SPEED)
  {
    servo360_speedControl(p);
    _fbs[p].speedOut = _fbs[p].opPidV;
  }   
  else if(_fbs[p].csop == S360_GOTO)
  {
    _fbs[p].ticksDiff = _fbs[p].angleTarget - _fbs[p].angle;
    _fbs[p].ticksGuard = ( _fbs[p].speedReq * abs(_fbs[p].speedReq) ) / (110 * _fbs[p].rampStep);
    //ticksGuard = ticksGuard * S360_UNITS_ENCODER / unitsRev;
    if((_fbs[p].ticksDiff < 0) && (_fbs[p].ticksDiff < _fbs[p].ticksGuard) && (_fbs[p].approachFlag == 0))
    {
      _fbs[p].speedReq = -_fbs[p].speedLimit;
      //servo360_speedControl(p);
      //_fbs[p].speedOut = _fbs[p].opPidV;
      _fbs[p].approachFlag = 0;
    }
    else if((_fbs[p].ticksDiff > 0) && (_fbs[p].ticksDiff > _fbs[p].ticksGuard) && (_fbs[p].approachFlag == 0))
    {
      _fbs[p].speedReq = _fbs[p].speedLimit;
      //servo360_speedControl(p);
      //_fbs[p].speedOut = _fbs[p].opPidV;
      _fbs[p].approachFlag = 0;
    }
    else if((_fbs[p].ticksDiff > 0) && (_fbs[p].ticksDiff <= _fbs[p].ticksGuard) && (_fbs[p].approachFlag == 0))
    {
      //speedReq -= rampStep;
      _fbs[p].speedReq = 0;
      _fbs[p].approachFlag = 1;
      //servo360_speedControl(p);
      //_fbs[p].speedOut = _fbs[p].opPidV;
    }    
    else if((_fbs[p].ticksDiff < 0) && (_fbs[p].ticksDiff >= _fbs[p].ticksGuard) && (_fbs[p].approachFlag == 0))
    {
      //speedReq += rampStep;
      _fbs[p].speedReq = 0;
      _fbs[p].approachFlag = 1;
      //servo360_speedControl(p);
      //_fbs[p].speedOut = _fbs[p].opPidV;
    } 
    else
    {
      //servo360_speedControl(p);
      //_fbs[p].speedOut = _fbs[p].opPidV;
    }       
    
    servo360_speedControl(p);
    _fbs[p].speedOut = _fbs[p].opPidV;
    
    if
    ( 
      (abs(_fbs[p].ticksDiff) < (_fbs[p].rampStep / (_fbs[p].unitsRev * 50))) 
      || (_fbs[p].approachFlag == 1 && _fbs[p].speedMeasured == 0)
    )
    {
      _fbs[p].speedReq = 0;
      _fbs[p].speedTarget = 0;
      _fbs[p].sp = _fbs[p].angleTarget;
      _fbs[p].csop = S360_POSITION;
      _fbs[p].approachFlag = 0;
      //return;
    }      
  }
  else if(_fbs[p].csop == S360_MONITOR)
  {
    
  } 
}


int servo360_dutyCycle(int p, int scale)
{
  int t = CNT;
  int dt = 3 * (CLKFREQ/1000);
  
  int pin = _fbs[p].pinFb;
  CTRA = (1000 << 26) | pin;
  CTRB = (1100 << 26) | pin;
  FRQA = 1;
  FRQB = 1;
  
  int mask = 1 << pin;
  int phsa, phsb;
  
  while(INA & mask) if(CNT - t > dt) break;
  PHSA = 0;
  while(!(INA & mask)) if(CNT - t > dt) break;
  PHSB = 0;
  while(INA & mask) if(CNT - t > dt) break;
  phsa = PHSA;
  while(!(INA & mask)) if(CNT - t > dt) break;
  phsb = PHSB;
  
  CTRA = 0;
  CTRB = 0;

  int dc = (phsa * scale) / (phsa + phsb);
  
  if(CNT - t > dt)
  {
    return -1;
  }
  else
  {    
    return dc;
  }    
}  


int servo360_getTheta(int p)
{
  _fbs[p].dc = servo360_dutyCycle(p, S360_M); 
  
  if(_fbs[p].angleSign == S360_CCW_POS)
  {
    _fbs[p].theta = (S360_ENC_RES - 1) - (_fbs[p].dc + S360_B);
  }
  else if(_fbs[p].angleSign == S360_CCW_NEG)
  {    
    _fbs[p].theta = _fbs[p].dc + S360_B;
  }  

  _fbs[p].theta &= 0xFFF;
  return _fbs[p].theta;
}  


int servo360_crossing(int current, int previous, int units)
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


void servo360_setPositiveDirection(int p, int direction)
{
  _fbs[p].angleSign = direction;
}  


// Angular PID control
int servo360_pidA(int p)
{
  // Clear any speed control system corrections so that return to speed control
  // doesn't start with unexpected compensation.
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
  
  // Angle error
  _fbs[p].er = _fbs[p].sp - _fbs[p].angle;
  // Integral accumuliation
  _fbs[p].integral += _fbs[p].er;
  // Derivative difference
  _fbs[p].derivative = _fbs[p].er - _fbs[p].erP;
  
  // Clamp itegral level
  if(_fbs[p].integral > _fbs[p].iMax) _fbs[p].integral = _fbs[p].iMax;
  if(_fbs[p].integral < _fbs[p].iMin) _fbs[p].integral = _fbs[p].iMin;

  // Calculate influences of P, I, and D.
  _fbs[p].p = (_fbs[p].Kp * _fbs[p].er) / S360_SCALE_DEN_A;
  _fbs[p].i = (_fbs[p].Ki * _fbs[p].integral) / S360_SCALE_DEN_A;
  _fbs[p].d = (_fbs[p].Kd * _fbs[p].derivative) / S360_SCALE_DEN_A;
  
  // Output = sum(P, I, and D)
  _fbs[p].op = (_fbs[p].p + _fbs[p].i + _fbs[p].d);
  
  // Limit output proportional to speed limit???  This may have been intended
  // to be proportional to the current target speed.
  //int opMax = _fbs[p].speedLimit / 4;
  //int opMax = _fbs[p].speedLimit;
  
  if(_fbs[p].op > _fbs[p].opMax) _fbs[p].op = _fbs[p].opMax;
  if(_fbs[p].op < -_fbs[p].opMax) _fbs[p].op = -_fbs[p].opMax;
  
  _fbs[p].erP = _fbs[p].er;
  return _fbs[p].op;
}
  
  
// Velocity PID control
// Calculated distance marches forward based on speed.  The control system 
// calculates position error at 50 Hz by subtracting actual position from 
// calcualted position.  This is the error that is the basis for the 
// P, I, and D calculations.   
int servo360_pidV(int p)  
{
  //while(lockset(_fb360c.lock360));

  //int opv;  
  int opMax = _fbs[p].speedLimit;

  _fbs[p].speedMeasured = (_fbs[p].angle - _fbs[p].angleP) * 50; 
  if(abs(_fbs[p].angleError) < S360_UNITS_ENCODER/4)
  {
    _fbs[p].angleDeltaCalc = _fbs[p].speedTarget / S360_CS_HZ;
    _fbs[p].angleCalc += _fbs[p].angleDeltaCalc;
  }    

  _fbs[p].angleError = _fbs[p].angleCalc - _fbs[p].angle;

  if(abs(_fbs[p].angleError) < S360_UNITS_ENCODER/4)
  {
    _fbs[p].erDist = _fbs[p].angleError;
    _fbs[p].integralV += _fbs[p].erDist;
    _fbs[p].derivativeV = _fbs[p].erDist - _fbs[p].erDistP;
  }    
  
  if(_fbs[p].integralV > _fbs[p].iMaxV) _fbs[p].integralV = _fbs[p].iMaxV;
  if(_fbs[p].integralV < _fbs[p].iMinV) _fbs[p].integralV = _fbs[p].iMinV;

  _fbs[p].pV = (_fbs[p].KpV * _fbs[p].erDist) / S360_SCALE_DEN_V;
  _fbs[p].iV = (_fbs[p].KiV * _fbs[p].integralV) / S360_SCALE_DEN_V;
  _fbs[p].dV = (_fbs[p].KdV * _fbs[p].derivativeV) / S360_SCALE_DEN_V;
  
  _fbs[p].opV = _fbs[p].pV + _fbs[p].iV + _fbs[p].dV;

  if(_fbs[p].opV > opMax) _fbs[p].opV = opMax;
  if(_fbs[p].opV < -opMax) _fbs[p].opV = -opMax;
  
  _fbs[p].erDistP = _fbs[p].erDist;
  
  //lockclr(_fb360c.lock360);  

  return _fbs[p].opV;
}


// Select pulse width from graph of angular velocity vs. pulse width
// for the servo.  This is done once for each new speed.  After the pulse
// is delivered once, the control system adjusts upward or downward from
// that initial value.
int servo360_upsToPulseFromTransferFunction(int unitsPerSec)
{
  int pw, b, mx;
  int ups = unitsPerSec/7;
  
  if(ups > 0)
  {
    mx = ups;
    b = S360_B_POS;
    pw = mx + b;
  }
  else if(ups < 0)
  {
    mx = ups;
    b = S360_B_NEG;
    pw = mx + b;
  }    
  else
  {
    pw = 15000;
  }
  return pw;    
}  


void servo360_speedControl(int p)
{
  // If we switch back to position control, it doesn't
  // work well to have old settings error correction from
  // the last time position was controlled, so clear the
  // settings.
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

  // Acceleration control by taking steps in target speed 
  // toward requested speed
  if(_fbs[p].speedTarget != _fbs[p].speedReq)
  {
    int speedDifference = _fbs[p].speedReq - _fbs[p].speedTarget;
    if(abs(_fbs[p].angleError) < S360_UNITS_ENCODER/4)
    {
      if( abs(speedDifference) > _fbs[p].rampStep)
      {
        if(speedDifference > 0)
        {
          _fbs[p].speedTarget += _fbs[p].rampStep;
        }
        else if(speedDifference < 0)
        {
          _fbs[p].speedTarget -= _fbs[p].rampStep;
        }        
      }
      else
      {
        _fbs[p].speedTarget = _fbs[p].speedReq;
        //speedUpdateFlag = 0;
      }
    }      
    _fbs[p].pw = servo360_upsToPulseFromTransferFunction(_fbs[p].speedTarget);
    _fbs[p].drive = _fbs[p].pw - 15000;
    _fbs[p].opPidV = _fbs[p].drive + servo360_pidV(p);
  }
  else    
  {
    _fbs[p].opPidV = _fbs[p].drive + servo360_pidV(p);
  }
  _fbs[p].speedTargetP = _fbs[p].speedTarget;
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
