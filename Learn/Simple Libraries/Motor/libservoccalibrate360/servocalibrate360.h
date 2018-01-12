/**
 * @file abcalibrate.h
 *
 * @author Andy Lindsay
 *
 * @copyright Copyright (C) Parallax, Inc. 2013.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This library has a function you can call to calibrate your 
 * ActivityBot.  Example code that uses this library to calibrate the
 * ActivityBot is here:
 * <br>
 * <br>
 * http://learn.parallax.com/activitybot
 * <br>
 * <br>
 * Calibration instructions that accompany the example code are included in the tutorial.
 *
 * @par Core Usage
 * A call to cal_activityBot launches 2 additional cores, and self-terminates the
 * application when done.  
 *
 * @par EEPROM Usage
 * Writes to addresses 63418..65470. 
 *
 * @par Memory Models
 * Use with CMM. 
 *
 * @version 0.91
 * @li add cal_servoPins and cal_encoderPins to change from default
 * I/O connections to ActivityBot servos and encoders.  Values used
 * will persist in EEPROM and be used by the abdrive library.
 * 
 * @version v0.90 
 *
 * @par Help Improve this Library
 * Please submit bug reports, suggestions, and improvements to this code to
 * editor@parallax.com.
 */

#ifndef SERVOCALIBRATE_H
#define SERVOCALIBRATE_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"
#include "servo360.h"


#ifndef _SERVO_CAL_360_EE_Start_
/**
 *
 * @brief ActivityBot EEPROM calibration data start address.
 */
#define _SERVO_CAL_360_EE_Start_  39728
#endif

#ifndef _SERVO_CAL_360_EE_PinCTRL_
#define _SERVO_CAL_360_EE_PinCTRL_ 4
#endif

#ifndef _SERVO_CAL_360_EE_PinFB_
#define _SERVO_CAL_360_EE_PinFB_ 8
#endif

#ifndef _SERVO_CAL_360_EE_mVccw_
#define _SERVO_CAL_360_EE_mVccw_ 12
#endif

#ifndef _SERVO_CAL_360_EE_bVccw_
#define _SERVO_CAL_360_EE_bVccw_ 16
#endif

#ifndef _SERVO_CAL_360_EE_mVcw_
#define _SERVO_CAL_360_EE_mVcw_ 20
#endif

#ifndef _SERVO_CAL_360_EE_bVcw_
#define _SERVO_CAL_360_EE_bVcw_ 24
#endif

#ifndef _SERVO_CAL_360_EE_Cal_Rec_Length_
#define _SERVO_CAL_360_EE_Cal_Rec_Length_ 28
#endif

#ifndef _SERVO_CAL_360_EE_End_
/**
 *
 * @brief ActivityBot EEPROM calibration data end address.
 */
#define _SERVO_CAL_360_EE_End_ _SERVO_CAL_360_EE_Start_ + (28 * 14)   // = 28 * 14 = 392
#endif


/**
 * @brief Run the ActivityBot calibration function.  Let it run until the
 * P26 and P27 lights turn off.  It'll take about 1 minute, 20 seconds.
 */ 
void cal_servo360(int pinControl, int pinFeedback);


void cal_displayData(int pinControl);
void cal_displayResults(int pinControl);
void cal_clear(int pinControl);


#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* ABCALIBRATE_H */  

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
