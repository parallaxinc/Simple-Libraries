/**
 * @file simpletools.h
 *
 * @author Andy Lindsay
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2013-2017. All Rights MIT Licensed.
 *
 * @brief This library provides convenient functions 
 *
 * @version 0.91 shift_in function pre-clock mode bug fixed. @n @n
 * 
 * @par Help Improve this Library
 * Please submit bug reports, suggestions, and improvements to this code to
 * editor@parallax.com.
 */

#ifndef PWM2CH_H
#define PWM2CH_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"

typedef struct pwm2ch_st
{
  volatile unsigned int tCycle;
  volatile unsigned int ticksA;
  volatile unsigned int ticksB; 
  volatile unsigned int ctra; 
  volatile unsigned int ctrb;
  volatile unsigned int pin;
  volatile int pwm2cog;
  int pwm2stack[100];
} pwm2ch_t;

typedef pwm2ch_t pwm2ch;

  

/**
 * @brief Start pulse width modulation (PWM) process in another cog.
 *
 * @details Great for DC motors, can also be used for servos, but the 
 * servo library is probably a better choice for that.
 *
 * A PWM signal sends repeated high signals with a fixed cycle time.
 * Your code will typically control the amount of time a PWM signal is
 * high during each cycle.  For example, pwm_start(1000) will establish
 * a 1000 us PWM cycle.  You can then use the pwm_set function to send
 * high signals that last anywhere from 0 to 1000 us.   
 *
 * @param cycleMicroseconds Number of microseconds the PWM cycle lasts.
 */
pwm2ch * pwm2ch_start(unsigned int cycleMicroseconds);

/**
 * @brief Set a PWM signal's high time.
 *
 * @details After a single call to pwm_start, this function allows you
 * to set a PWM signal's high time.  For example, if your pwm_start call
 * sets up 1000 us (1 ms) you could use this function to make the signal
 * high for 3/4 of its cycle with pwm_set(pin, channel, 750).  If the
 * signal goes to a DC motor through an H bridge or other driver circuit,
 * the motor will behave as though it's only getting 3/4 of the supply 
 * and turn at roughly 3/4 of full speed.
 *
 * @param pin I/O pin to send the PWM signal.  You can change this 
 * value on the fly, which is useful for speed control of a DC motor in 
 * two different directions.  When the PWM signal changes to a new pin,
 * the cog sets the previous pin to input.  If you want it to stay low
 * when the PWM cog lets go, just set the pin low in your code before 
 * calling pwm_start.
 * 
 * @param channel You have options of 0 or 1 for up to two simultaneous 
 * PWM signals.  If you have an application in mind that requires more
 * PWM signals, check the SimpleIDE/Learn/Simple Libraries/Motor
 * directory, and also online at obex.parallax.com. 
 *
 * @param tHigh The high time for each PWM cycle repetition.
 */
void pwm2ch_set(pwm2ch *device, int pin, int channel, int tHigh);

/**
 * @brief Shut down PWM process and reclaim cog and I/O pins for other
 * uses.
 *
 * @details Shut down PWM process and reclaim cog and I/O pins for other uses
 *
 */
void pwm2ch_stop(pwm2ch *device);


/**
 * @}
 */
 
 

#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* SIMPLETOOLS_H */  

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
