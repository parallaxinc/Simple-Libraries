/*
  @file console.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
//#include "servo.h" 
#include "servo360.h"

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

//servo360 fb[2];

fdserial *term;

void console_start()
{
  simpleterm_close();
  pause(10);
  cntPrev = CNT;
  cog_run(console, 512);
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
    //fb360_run();
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
    fb360_waitServoCtrllEdgeNeg(0);
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
      //fb360_waitServoCtrllEdgeNeg(0);
      dprint(term, "ms: %d\r", tElapsed / (CLKFREQ/1000)); 
      for(int p = 0; p < devCount; p++)
      {
        dprint(term, "id: %d, csop: %d, ms: %d\r", p, fb[p].csop, tElapsed / (CLKFREQ/1000)); 
        if(fb[p].csop == POSITION)
        {
          dprint(term, "pv: %d, op: %d, e: %d, p: %d, i: %d, d: %d th: %d\r", 
               fb[p].angle, fb[p].op, fb[p].er, fb[p].p, fb[p].i, fb[p].d, fb[p].theta); 
        }        
        //else if(operation == SPEED)
        else if(fb[p].csop == SPEED)
        {
          dprint(term, "spR: %d, spT: %d, spM: %d, "\
                       "drive: %d, opV: %d, opPidV: %d, "\
                       "dcaC: %d, dcaM: %d, dcaE: %d\r", 
                       fb[p].speedReq, fb[p].speedTarget, fb[p].speedMeasured, 
                       fb[p].drive, fb[p].opV, fb[p].opPidV, 
                       fb[p].angleCalc, fb[p].angle, fb[p].angleError); 
        }        
        else if(fb[p].csop == GOTO)
        {
          dprint(term,         
                   "spR: %d, spT: %d, spM: %d, "\
                   "csop: %d, aT: %d, a: %d, "\
                   "tG: %d, tD: %d, af: %d\r", 
                   fb[p].speedReq, fb[p].speedTarget, fb[p].speedMeasured, 
                   fb[p].csop, fb[p].angleTarget, fb[p].angle,
                   fb[p].ticksGuard, fb[p].ticksDiff, fb[p].approachFlag 
                 ); 
        }        
        //else if(operation == MONITOR)
        else if(fb[p].csop == MONITOR)
        {
          //dprint(term, "th: %d, pvm: %d\r", 
          //       theta, angleFixed); 
          //if(( angleFixed > (angleFixedPrev + 30) || (angleFixed < angleFixedPrev - 30))) dprint(term, "\r\r\rLOOK???   LOOK!!!   LOOK!!!\r\r\r");        
          //angleFixedPrev = angleFixed;
          dprint(term, "dc: %d, theta: %d, turns: %d, angle: %d\r", 
          fb[p].dc, fb[p].theta, fb[p].turns, fb[p].angle);
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
