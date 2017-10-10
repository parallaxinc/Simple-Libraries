/*
  @file abdrive360.c

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "abdrive360.h"


//                                            //                                //  


volatile int abd360_initialized = 0;

volatile int abd360_unitsPerRev = ABD360_UNITS_REV;

volatile int abd360_pinCtrlLeft = ABD60_PIN_CTRL_L;
volatile int abd360_pinCtrlRight = ABD360_PIN_CTRL_R;
volatile int abd360_pinFbLeft = ABD60_PIN_FB_L;
volatile int abd360_pinFbRight = ABD360_PIN_FB_R;

volatile int abd360_speedLimit = ABD_SPEED_LIMIT;
volatile int abd360_rampStep = ABD_RAMP_STEP;
volatile int abd360_speedLimitGoto = ABD_GOTO_SPEED_LIMIT;
volatile int abd360_rampStepGoto = ABD_GOTO_RAMP_STEP;

volatile int abd360_gotoMode = ABD360_GOTO_BLOCK;

void drive_init(void)
{
<<<<<<< HEAD
  patch360forBlockly();

  abdrive360_getEepromPins();
  
=======
>>>>>>> parent of cf415cb... abdrive360/servo360 - try EEPROM calibration / transfer function adjusting functions #151
  int result, flag = 0;
  do
  {
    result = servo360_connect(abd360_pinCtrlLeft, abd360_pinFbLeft);
    if(result < 0) flag = 1;
  }    
  while(result < 0);

  do
  {
    result = servo360_connect(abd360_pinCtrlRight, abd360_pinFbRight);
    if(result < 0) flag = 1;
  }    
  while(result < 0);
  
  if(flag) pause(200);  // PWR 1 -> 2, let servos engergize

  servo360_setUnitsFullCircle(abd360_pinCtrlLeft, ABD360_UNITS_REV);
  servo360_setUnitsFullCircle(abd360_pinCtrlRight, ABD360_UNITS_REV);

  servo360_setAcceleration(abd360_pinCtrlLeft, abd360_rampStep * 50);
  servo360_setAcceleration(abd360_pinCtrlRight, abd360_rampStep * 50);

  servo360_setMaxSpeed(abd360_pinCtrlLeft, abd360_speedLimit);
  servo360_setMaxSpeed(abd360_pinCtrlRight, abd360_speedLimit);

  servo360_couple(abd360_pinCtrlLeft, abd360_pinCtrlRight);
  
  /*
  #define S360_KPA 5000
  #define S360_KIA 150
  #define S360_KDA 0
  #define S360_POS_INTGRL_MAX 150
  #define S360_SCALE_DEN_A 1000
  */

  servo360_setControlSys(abd360_pinCtrlLeft, S360_SETTING_KPA, 5000);             // KPV
  servo360_setControlSys(abd360_pinCtrlRight, S360_SETTING_KPA, 5000);             // KPV
  servo360_setControlSys(abd360_pinCtrlLeft, S360_SETTING_KIA, 150);               // KIV
  servo360_setControlSys(abd360_pinCtrlRight, S360_SETTING_KIA, 150);               // KIV
  servo360_setControlSys(abd360_pinCtrlLeft, S360_SETTING_KDA, 0);               // KDV
  servo360_setControlSys(abd360_pinCtrlRight, S360_SETTING_KDA, 0);               // KDV
  servo360_setControlSys(abd360_pinCtrlLeft, S360_SETTING_IA_MAX, 150);            // FB360_VEL_INTGRL_MAX
  servo360_setControlSys(abd360_pinCtrlRight, S360_SETTING_IA_MAX, 150);            // FB360_VEL_INTGRL_MAX

  abd360_initialized = 1;
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
