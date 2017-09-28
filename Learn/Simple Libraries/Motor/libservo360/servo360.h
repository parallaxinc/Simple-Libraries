//#define _console_

/*
  @file servo360.h

  @author Parallax Inc

  @copyright
  Copyright (C) Parallax Inc. 2017. All Rights MIT Licensed.  See end of file.
 
  @brief 
*/


#include "simpletools.h"  

#ifdef _console_
  #include "fdserial.h"
#endif

#define UNITS_FULL_CIRCLE 360
#define MAX_SPEED 2 * 4096 
#define B_POS (int) 15200
#define B_NEG (int) 14800

#define DUTY_CYCLE_MIN 290
#define DUTY_CYCLE_MAX 9710

#define CCW_POS 1
#define CCW_NEG -1

#define SPEED 1
#define POSITION 2
#define GOTO 3
#define MONITOR 4
#define servo360_FREQ_CTRL_SIG 50
#define servo360_DEVS_MAX 2

#define servo360_RAMP_STEP 10 * 4096 / 360;

#define servo360_M 4348
#define servo360_B -129
#define servo360_ENC_RES 4096

#define KPA 12000
#define KIA 600
#define KDA 6000
#define servo360_POS_INTGRL_MAX 600
#define SCALE_DEN_A 1000

/*
#define KPV 3000
#define KIV 500
#define KDV 1600
#define servo360_VEL_INTGRL_MAX 325
*/
#define KPV 2500
#define KIV 0
#define KDV 0
#define servo360_VEL_INTGRL_MAX 0
#define SCALE_DEN_V 1000

#define PW_CENTER 15000
#define servo360_CS_HZ 50
#define UNITS_ENCODER 4096
#define UNITS_REV 360

#define S360_KPV 1
#define S360_KIV 2
#define S360_KDV 3
#define S360_IV_MAX 4
#define S360_KPA 5
#define S360_KIA 6
#define S360_KDA 7
#define S360_IA_MAX 8

//#define S360_A_MAX (((1 << 31) - 1)) / UNITS_FULL_CIRCLE  // 524287 degrees
#define S360_A_MAX 524287          


/* Public */
int servo360_connect(int pinControl, int pinFeedback);

int servo360_setUnitsFullCircle(int pin, int units);
int servo360_getUnitsFullCircle(int pin);

int servo360_setMaxSpeed(int pin, int speed);
int servo360_getMaxSpeed(int pin);

int servo360_speed(int pin, int speed);
int servo360_getSpeed(int pin);
int servo360_getAngleCalc(int pin);

int servo360_angle(int pin, int position);
int servo360_getAngle(int pin);

int servo360_goto(int pin, int position);
int servo360_getCsop(int pin);

int servo360_getAngle12Bit(int pin);
int servo360_getAngleFixedOrigin(int pin);

int servo360_setAcceleration(int pin, int unitsPerSecSquared);
int servo360_getAcceleration(int pin);

int servo360_setRampStep(int pin, int stepSize);
int servo360_getRampStep(int pin);

int servo360_setControlSys(int pin, int constant, int value);
int servo360_getControlSys(int pin, int constant);

int servo360_setAngleLimits(int pin, int ccwMax, int cwMax);
int servo360_getAngleLimits(int pin, int *ccwMax, int *cwMax);

int servo360_setTurns(int pin, int turns);
int servo360_getTurns(int pin);

int servo360_stop(int pin);

int servo360_feedback(int pin, int state);
int servo360_set(int pinControl, int time);

int servo360_setAngleCtrlSpeedMax(int pin, int speed);
int servo360_getAngleCtrlSpeedMax(int pin);


// int servo360_enable(int pin, int state);

/* Private */
void servo360_run(void);
void servo360_end();
void servo360_setup(void);
void servo360_mainLoop();
void servo360_outputSelector(int p);

void servo360_servoPulse(int p, int q);
void servo360_waitServoCtrllEdgeNeg(int p);
int servo360_dutyCycle(int p, int scale);
int servo360_crossing(int current, int previous, int units);
int servo360_getTheta(int p);
void servo360_checkAngle(int p);
void servo360_captureOffset(int p);
void servo360_setPositiveDirection(int p, int direction);

int servo360_setRampStep(int p, int stepSize);

int servo360_upsToPulseFromTransferFunction(int unitsPerSec);
void servo360_pulseControl(int p, int speedUps);

void servo360_speedControl(int p);
int servo360_pidA(int p);
int servo360_pidV(int p);  

int servo360_findServoIndex(int pin);

int servo360_unitsAngleToEncoder(int value, int unitsRev);
int servo360_unitsEncoderToAngle(int value, int unitsRev); 
int servo360_checkDistanceRemaining(int pin, int speed, int finalAngle);

int servo360_setMaxSpeedEncoded(int pin, int speed);

void servo360_consoleRun(void);
void servo360_consoleEnd(void);

#ifdef _console_
void console();
void console_start(void);
void console_stop();
int terminal_checkForValue(fdserial *connection, int *value);
#endif

                           ////// ALL SERVOS //////

//extern fdserial *term;
extern int *servoCog;
extern volatile int lock360;
extern volatile int t360;
extern volatile int t360slice;
extern volatile int dt360fbSlice;
extern volatile int dt360spSlice;
extern volatile int devCount;
extern volatile int pulseCount;
//extern volatile int SCALE_DEN_V;                     // Velocity control system denomenator


                            ////// PER SERVO ///  ///
  
typedef volatile struct servo360_s {
  // settings
  volatile int pinCtrl;                       // pinControl
  volatile int pinFb;                       // pinFeedback
  volatile int angleSign;
  volatile int rampStep;
  volatile int speedLimit;
  volatile int feedback;
  volatile int angleMax;
  volatile int angleMin;
  volatile int unitsRev;
  
  // admin
  volatile int csop;
  volatile int speedReq;
  
  // encoders
  volatile int dc, dcp;
  volatile int theta, thetaP;
  volatile int turns;
  volatile int angleFixed, angleFixedP; 
  volatile int angle, angleP, pvOffset;
  //volatile int stalled, noSignal;
  volatile int opMax;
  
  // pulse control
  volatile int speedOut;
  volatile int pw;
  
  // speed control system
  volatile int opPidV;
  volatile int approachFlag;
  volatile int ticksDiff;
  volatile int ticksGuard;
  volatile int angleCalc;
  volatile int angleDeltaCalc;
  volatile int angleError;
  volatile int erDist, erDistP;
  volatile int speedTarget;
  volatile int speedTargetP;
  volatile int integralV; 
  volatile int derivativeV;
  volatile int opV;
  volatile int iMaxV;
  volatile int iMinV;
  volatile int KpV;
  volatile int KiV;
  volatile int KdV;
  volatile int pV, iV, dV;
  volatile int speedMeasured;
  volatile int drive;
  volatile int stepDir;
  volatile int lag;
  
  // position control system
  volatile int Kp;
  volatile int Ki;
  volatile int Kd;
  volatile int er, erP;
  volatile int sp, integral, derivative;
  volatile int op, iMax, iMin;
  volatile int p, i, d;
  
  // goto system
  volatile int angleTarget;
} servo360_t;

extern volatile servo360_t fb[servo360_DEVS_MAX];

// console
#ifdef _console_
  fdserial *term;
  extern volatile int suppressFbDisplay;
#endif



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
