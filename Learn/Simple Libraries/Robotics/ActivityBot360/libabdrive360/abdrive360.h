/*
  @file abdrive360.h

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  
#include "servo360.h"

#define ABD60_PIN_CTRL_L 12
#define ABD60_PIN_FB_L 14

#define ABD360_PIN_CTRL_R 13
#define ABD360_PIN_FB_R 15

#define ABD360_UNITS_REV 64

#define ABD360_GOTO_BUSY 1
#define ABD360_GOTO_CLEAR 0

#define ABD360_GOTO_BLOCK 0
#define ABD360_GOTO_SET_FORGET 1

#define ABD_RAMP_STEP 12
#define ABD_SPEED_LIMIT 128
#define ABD_GOTO_SPEED_LIMIT 64
#define ABD_GOTO_RAMP_STEP 4

#define AB360_NEITHER 0
#define AB360_LEFT 1
#define AB360_RIGHT 2

//#define ABD_NUDGE_SPEED 4
//#define ABD_STOP_50ths 5

#define FOR_GOTO 1
#define FOR_SPEED 0
#define OFF 0
#define ON  1
#define SIDE_LEFT 0
#define SIDE_RIGHT 1
#define SIDE_BOTH 2

extern volatile int abd360_initialized;

extern volatile int abd360_unitsPerRev;

extern volatile int abd360_pinCtrlLeft;
extern volatile int abd360_pinCtrlRight;
extern volatile int abd360_pinFbLeft;
extern volatile int abd360_pinFbRight;

extern volatile int abd360_speedLimit;
extern volatile int abd360_rampStep;
extern volatile int abd360_setRampStep;
extern volatile int abd360_speedLimitGoto;
extern volatile int abd360_rampStepGoto;

extern volatile int abd360_gotoMode;


void drive_init(void);

void drive_goto(int distLeft, int distRight);

void drive_speed(int left, int right); 

void drive_getTicks(int *left, int *right);

void drive_calibrationResults(void);

void drive_getTicksCalc(int *left, int *right);

int drive_gotoStatus(int side);

void drive_encoderPins(int encPinLeft, int encPinRight);

void drive_feedback(int enabled); 

void drive_abd360_gotoMode(int mode);

void drive_servoPins(int servoPinLeft, int servoPinRight);

void drive_setAcceleration(int forGotoOrSpeed, int ticksPerSecSq);

void drive_setErrorLimit(int maxDistDiffTicks);

void drive_setMaxSpeed(int speed);

void drive_setMaxVelocity(int forGotoOrSpeed, int ticksPerSec);

void drive360_ticksPerRev(int units);

void drive_setRampStep(int stepsize);

void drive_abd360_rampStep(int left, int right);

void drive_ramp(int left, int right);

void drive_rampStep(int left, int right);



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
