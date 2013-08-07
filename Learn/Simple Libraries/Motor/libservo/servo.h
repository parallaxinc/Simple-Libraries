/**
 * @file servo.h
 *
 * @author Andy Lindsay
 *
 * @version 0.85
 *
 * @copyright Copyright (C) Parallax, Inc. 2012.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Control servos in other cog.  Currently up to 7, but more should
 * be coming soon.  
 * @n @n Currently supports LMM and CMM memory models.  
 *
 * @details This library automatically delivers 
 * control pulses to the servos every 20 ms, all you have to do is use the set 
 * method to pick the pin the servo is connected to and the duration of the 
 * control pulses.
 *
 * Parallax standard servos have a position range from approximately 0 to 180
 * degrees.  For 0 degrees, use control pulses of
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */

#ifndef SERVO_H
#define SERVO_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"

/**
 * @brief Set Parallax Standard Servo to angle from 0 to 180 in tenths of
 * a degree.
 *
 * @details Examples:
 *
 * @code
 * servoAngle(pin, 0);     // for 0 degrees
 * servoAngle(pin, 900);   // for 90 degrees
 * servoAngle(pin, 1800);  // for 180 degrees
 * @endcode
 *
 * 0 to 1800 corresponds to control pulses ranging from 500 to 2300 with 1400
 * at center (90 degrees), which is slightly different from the 1500 center
 * convention, but it places the servo's range of motion neatly between its
 * mechanical limits.
 *
 * @param pin Number of the I/O pin connected to servo
 * @param degreeAngle Tenths of a degree from 0 to 1800
 *
 * @returns 1 if successful, 0 if no cogs or 1 if no locks.
 */
int servo_angle(int pin, int degreeTenths);

/**
 * @brief Set Parallax Continous Rotation Servo speed.
 *
 * @details Examples:
 *
 * @code
 * servoSpeed(pin, 200);    // Twice full speed counterclockwise
 * servoSpeed(pin, 100);    // Full speed counterclockwise
 * servoSpeed(pin, 0);      // Stay still
 * servoSpeed(pin, -100);   // Full speed clockwise
 * servoSpeed(pin, -200);   // Twice full speed clockwise
 * @endcode
 *
 * 100 to -100 corresponds to the linear speed control range.  For example,
 * servoSpeed(pin, 75) will set the speed to roughly 75% of full speed
 * counterclockwise.  This is a very rough approximation.
 *
 * @param pin Number of the I/O pin connected to servo
 * @param degreeAngle Tenths of a degree from 0 to 1800
 *
 * @returns 1 if successful, 0 if no cogs or 1 if no locks.
 */
int servo_speed(int pin, int speed);

/**
 * @brief Sets servo control signal to servo connected to a given pin.
 *
 * @details This function directly controls the number of microseconds servo
 * control pulses last.
 *
 * Examples:
 *
 * @code
 * servoSet(pin, 500);    //   0 degrees
 * servoSet(pin, 1400);   //  90 degrees
 * servoSet(pin, 2300);   // 180 degrees
 * @endcode
 *
 * 500, 1400, and 2300 are the number of microseconds (us) the control pulses
 * stay high.  More generally, a microsecond above 500 corresponds to 1/10
 * of a degree clockwise of 0 degrees.  So, for a given degree position, use:
 *
 *   degree position = 500 + (number of 10ths of a degree)
 *
 * For setting continuous rotation servo speed, use:
 *
 * @li Full speed clockwise        -> servoSet(pin, 1400);
 * @li Stay still                  -> servoSet(pin, 1500);
 * @li Full speed counterclockwise -> servoSet(pin, 1600);
 *
 * Values in the 1400 to 1600 range are (roughly) proportional to speed, but
 * it's not nearly as precise as position control.  Setting full speeds at
 * 1300 and 1700 is a common practice to make sure both servos are going as
 * fast as they possibly can.
 *
 * @param pin Number of the I/O pin that sends signals to the servo
 *
 * @returns .
 */
int servo_set(int pin, int time);

/**
 * @brief Set the maximum change in control signal a servo will change
 * in a given 20 ms time period.
 *
 * @details This function allows you to make a Parallax Continuous Rotation
 * servo ramp up to and down from whatever speed it was previously set to.  It
 * also allows you to set the rate at which a Parallax Standard Servo turns
 * from its previous position to a new position.
 *
 * @param pin Number of the I/O pin the servo is connected to
 * @param stepSize The number of microseconds per 20 ms of time that the servo's
 * control signal is allowed to change.  This equates to the number of tenths of
 * a degree a Parallax Standard Servo is allowed to change, or the number of
 * 100ths of full speed the a Parallax Continuous Rotation servo is allowed to
 * change per 20 ms.
 *
 * @returns 1 if successful, 0 if pin not found.
 */
int servo_setramp(int pin, int stepSize);

/**
 * @brief Reports the number of microseconds of the pulse most recently sent
 * to a given servo.
 *
 * @param pin Number of the I/O pin the servo is connected to
 *
 * @returns tp[i] The value stored by the array element that keeps duration
 * of the most recent pulse sent to the servo. (Or -1 if an entry is not found
 * for the pin argument.
 */
int servo_get(int pin);

/**
 * @brief Stops the servo process and frees a cog.
 */
void servo_stop(void);

/**
 * @brief Starts the servo process and takes over a cog.
 *
 * @details You do not need to call this function from your code because
 * the servoSet function calls it if it detects that the servo cog has not
 * been started.
 *
 * @returns 1..8 if successful.  0 if no available cogs, -1 if no available
 * locks.
 */
int servo_start(void);

#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif

/* SERVO_H */  

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
