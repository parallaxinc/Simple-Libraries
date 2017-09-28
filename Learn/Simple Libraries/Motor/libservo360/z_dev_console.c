/*
  @file console.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"


void servo360_consoleRun(void)
{
  #ifdef _console_
  pause(1000);
  
  // To use this, recompile libservo360 with #define _console_ uncommented
  // in servo360.h
  //
    //simpleterm_close();
    console_start();
    suppressFbDisplay = 0;
    
    pause(1000);
  // 
  
  //pause(1000);
  #endif 
}  


void servo360_consoleEnd(void)
{
  #ifdef _console_
    suppressFbDisplay = 1;
    console_stop();
  #endif 
}  


#ifdef _console_
#include "fdserial.h"

volatile int suppressFbDisplay = 0;
static char bufcons[20];
static volatile int val;

static volatile int operation;
static volatile int pvStart;
static volatile int angleFixedPrev;
volatile int cntPrev;
volatile int tElapsed;
volatile int cnt;

servo360_t fbt[servo360_DEVS_MAX];

//servo360 fb[2];

fdserial *term;
int *consoleCog;


void console_start()
{
  simpleterm_close();
  pause(10);
  cntPrev = CNT;
  consoleCog = cog_run(console, 512);
  pause(100);
}  
  

void console_stop()
{
  cog_end(consoleCog);
  fdserial_close(term);
  pause(100);
  simpleterm_open();
  pause(500);
}  
  

void console()
{
  //int operation = 0;
  
  term = fdserial_open(31, 30, 0, 115200);
  pause(10);
  bufcons[0] = 0;
  
  //pvStart = 0;

  //int start(void)
  {
    //servo360_run();
    /////servo_speed(pinServoCtrl, 0);
    pause(200);
    pause(10);
    //fb[0].speedReq = 0;
    //speedReqP = 0;
  }    
  
  fdserial_rxFlush(term);
  fdserial_txFlush(term);
  dprint(term, "Enter value: ");
  
  int value = 0;
  int ready = 0;

  int abc = 0;
  
  //int dt = CLKFREQ/50;
  //int t = CNT;
  
  while(1)
  {
    servo360_waitServoCtrllEdgeNeg(devCount - 1);
    cnt = CNT;
    tElapsed = cnt - cntPrev;
    cntPrev = cnt;
    
    ready = terminal_checkForValue(term, &value);

    if(ready == ' ')
    {
      suppressFbDisplay = !suppressFbDisplay;
    }
    else if(ready == 'a' || ready == 'A')
    {
      operation = POSITION;
      dprint(term, "\rEnter angle: ");
    }
    else if(ready == 's' || ready == 'S')
    {
      operation = SPEED;
      dprint(term, "\rEnter speed: ");
    }        
    else if(ready == 'g' || ready == 'G')
    {
      operation = GOTO;
      fb[0].csop = GOTO;
      dprint(term, "\rGoto Mode: ");
    }        
    else if(ready == 'm' || ready == 'M')
    {
      operation = MONITOR;
      fb[0].csop = MONITOR;
      operation = MONITOR;
      dprint(term, "\rMonitor Mode: ");
    }        

    if(ready == 1)
    {
      dprint(term, "\rvalue = %d\r", value);
      dprint(term, "\rEnter value: ");
      if(operation == POSITION)
      {
        servo360_angle(12, value);
      }
      else if(operation == SPEED)
      {
        servo360_speed(12, value);
      }  
      else if(operation == GOTO)
      {
        servo360_goto(12, value);
      }  
      else if(operation == MONITOR)
      {
        //servo_speed(pinServoCtrl, value);
      }                      
      dprint(term, "sp = %d\r", fb[0].sp);
      dprint(term, "operation = %d\r", operation);
    }
    //if(1)
    //if(0)
    if(!suppressFbDisplay)
    {
      //while(lockset(lock360));
      //if(operation == POSITION)
      //servo360_waitServoCtrllEdgeNeg(0);
      //dprint(term, "pc: %d\r", tElapsed / (CLKFREQ/1000));
      
      //
      while(lockset(lock360));
      for(int p = 0; p < devCount; p++)
      {
        fbt[p] = fb[p];
      } 
      lockclr(lock360);
      //
      //int p 
      for(int p = 0; p < devCount; p++)
      {
        /*
        pc        pulse count
        id        servoID  
                  0 left, 1 right
        csop      control system operation
                  0 inactive, 1 speed, 2, angle, 3 goto
        */
        if(p == 0)
        {
          //dprint(term, "pc: %d, id: %d, csop: %d\r", pulseCount, p, fbt[p].csop); 
          dprint(term, "pc: %d, id: %d, csop: %d\r", pulseCount, p, fbt[p].csop); 
        }          
        if(fbt[p].csop == POSITION)
        {
          dprint(term, "sp: %d, pv: %d, op: %d, e: %d, "\
                       "p: %d, i: %d, d: %d th: %d\r", 
                       fbt[p].sp, fbt[p].angle, fbt[p].op, fbt[p].er, 
                       fbt[p].p, fbt[p].i, fbt[p].d, fbt[p].theta); 
        }        
        //else if(operation == SPEED)
        else if(fbt[p].csop == SPEED)
        {
          /*
            spR       speed requested                    in 4096ths per second
            spT       speed target           
            spM       speed measured
  
            aC        angle calculated                   in 4096ths of a full circle
            aM        angle measured
            aE        angle error
  
            tf        pulse widt from tranfer function   in 0.1 us units
            pidV      pid velocity output
            tf+pidV   pulse output
          */
          /*
          dprint(term, "spR: %d, spT: %d, spM: %d\r"\
                       "aC: %d, aM: %d, aE: %d\r"\
                       "pV: %d, iV: %d, dV: %d\r"\
                       "tf: %d, pidV: %d, tf+pidV: %d"\
                       "\r",
                       fbt[p].speedReq, fbt[p].speedTarget, fbt[p].speedMeasured, 
                       fbt[p].angleCalc, fbt[p].angle, fbt[p].angleError, 
                       fbt[p].pV, fbt[p].iV, fbt[p].dV,
                       fbt[p].drive, fbt[p].opV, fbt[p].opPidV); 
          */
          dprint(term, "spR: %d, spT: %d, spM: %d\r",
                       fbt[p].speedReq, fbt[p].speedTarget, fbt[p].speedMeasured);
          dprint(term, "aC: %d, aM: %d, aE: %d\r",
                       fbt[p].angleCalc, fbt[p].angle, fbt[p].angleError); 
          dprint(term, "pV: %d, iV: %d, dV: %d\r",
                       fbt[p].pV, fbt[p].iV, fbt[p].dV);
          dprint(term, "sd: %d, lag: %d, spdO: %d\r",
                       fbt[p].stepDir, fbt[p].lag, fbt[p].speedOut);
          dprint(term, "tf: %d, pidV: %d, tf+pidV: %d",
                       fbt[p].drive, fbt[p].opV, fbt[p].opPidV); 
          dprint(term, "\r");
          //
          /*
          dprint(term, "spT: %d, aC: %d, aM: %d, aE: %d",
          fbt[p].speedTarget, fbt[p].angleCalc, 
          fbt[p].angle, fbt[p].angleError);
          if(p == 0) dprint(term, "   |   ");
          */
        }                        
        else if(fbt[p].csop == GOTO)
        {
          dprint(term,         
                   "spR: %d, spT: %d, spM: %d, "\
                   "csop: %d, aT: %d, a: %d, "\
                   "tG: %d, tD: %d, af: %d\r", 
                   fbt[p].speedReq, fbt[p].speedTarget, fbt[p].speedMeasured, 
                   fbt[p].csop, fbt[p].angleTarget, fbt[p].angle,
                   fbt[p].ticksGuard, fbt[p].ticksDiff, fbt[p].approachFlag 
                 ); 
        }        
        //else if(operation == MONITOR)
        else if(fbt[p].csop == MONITOR)
        {
          //dprint(term, "th: %d, pvm: %d\r", 
          //       theta, angleFixed); 
          //if(( angleFixed > (angleFixedPrev + 30) || (angleFixed < angleFixedPrev - 30))) dprint(term, "\r\r\rLOOK???   LOOK!!!   LOOK!!!\r\r\r");        
          //angleFixedPrev = angleFixed;
          dprint(term, "dc: %d, theta: %d, turns: %d, angle: %d\r", 
          fbt[p].dc, fbt[p].theta, fbt[p].turns, fbt[p].angle);
        }    
      }
      dprint(term, "\r");             
      //lockclr(lock360);
    }
  } 
}    


int terminal_checkForValue(fdserial *connection, int *value)
{
  static int n;
  if(fdserial_rxCount(connection) > 0)
  {
    bufcons[n] = fdserial_rxChar(connection); 
    if((bufcons[n] >= ' ') && (bufcons[n] <= 'z'))
    {
      dprint(connection, "%c", bufcons[n]);
    }
    else
    {
      dprint(connection, "[%d]", bufcons[n]); 
    }  

    if
    (
         bufcons[n] == ' '
      || bufcons[n] == 'A'
      || bufcons[n] == 'a'
      || bufcons[n] == 'S'
      || bufcons[n] == 's'
      || bufcons[n] == 'M'
      || bufcons[n] == 'm'
      || bufcons[n] == 'G'
      || bufcons[n] == 'g'
    )
    {
      int temp = bufcons[n];
      fdserial_rxFlush(connection);
      return temp;
    }
    else if((bufcons[n] == '\r') || (bufcons[n] == '\n'))
    {
      sscan(bufcons, "%d", &val); 
      n = 0;
      bufcons[n] = 0;
      dprint(connection, "\rval = %d\r", val);
      dprint(connection, "Enter value: ");
      *value = val;
      return 1;
    }         
    n++;
    return 0;
  }      
}

#endif //_console_



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
