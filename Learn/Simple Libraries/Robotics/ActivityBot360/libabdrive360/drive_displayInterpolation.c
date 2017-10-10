/*
  @file drive_displayInterpolation.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "abdrive360.h"

volatile int abd360_initialized;

volatile int abd360_unitsPerRev;

volatile int abd360_pinCtrlLeft;
volatile int abd360_pinCtrlRight;
volatile int abd360_pinFbLeft;
volatile int abd360_pinFbRight;

volatile int abd360_speedLimit;
volatile int abd360_rampStep;
volatile int abd360_speedLimitGoto;
volatile int abd360_rampStepGoto;

volatile int abd360_gotoMode;


int drive_displayInterpolation(void)
{
  //if(!abd_us) abd_us = CLKFREQ/1000000; 
  
  unsigned char str[12];
  ee_getStr(str, 12, _AB360_EE_Start_);
  str[11] = 0;
  
  if(strcmp(str, "AB360      "))
  {
    //print("!!! AB360 SETTINGS NOT FOUND, RETURNING !!!\r");
    return -1;
  }   
  /*
  else
  for(int i = 0; i < 12; i++)
  {
    if(str[i] <= 'z' && str[i] >= ' ')
    {
      print("%c", str[i]);
    }
    else
    {
      print("[%d]", str[i]);
    }
  }    
  */
 
    
  int mVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwL_);
  int bVccwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwL_); 
  int mVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwL_); 
  int bVcwL = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwL_); 

  int mVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVccwR_); 
  int bVccwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVccwR_); 
  int mVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_mVcwR_); 
  int bVcwR = ee_getInt(_AB360_EE_Start_ + _AB360_EE_bVcwR_); 
  
  /*
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VM_CCW, mVccwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VB_CCW, bVccwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VM_CW, mVcwL);
  servo360_setTransferFunction(abd360_pinCtrlLeft, S360_SETTING_VB_CW, -bVcwL );

  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VM_CCW, mVccwR );
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VB_CCW, bVccwR);
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VM_CW, mVcwR);
  servo360_setTransferFunction(abd360_pinCtrlRight, S360_SETTING_VB_CW, -bVcwR);
  */

  /*
  print("Inverse Transfer Function Constants\r");
  print("for y = mx + b\r");
  print("y: offset from 15,000 in 0.1 us units\r");
  print("m: Slope in 0.1us/4096 rps\r");
  print("x: Desired speed in 4096ths of a revolution/second\r");
  print("b: number of 0.1 us increments added to 15000\r");
  print("\r===================================\r"); 
  print("\rLeft Servo, Counterclockwise\r");
  print("m = %d\r", mVccwL); 
  print("b = %d\r", bVccwL); 
  print("\rLeft Servo, Clockwise\r");
  print("m = %d\r", mVcwL); 
  print("b = %d\r", bVcwL); 
  
  print("\rRight Servo, Counterclockwise\r");
  print("m = %d\r", mVccwR); 
  print("b = %d\r", bVccwR); 
  print("\rRight Servo, Clockwise\r");
  print("m = %d\r", mVcwR); 
  print("b = %d\r", bVcwR);  
  */ 
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
