/**
  @file pwm2ch.h
 
  @author Andy Lindsay
 
  @copyright
  Copyright (C) Parallax, Inc. 2018. All Rights MIT Licensed.
 
  @brief Functions for up to 2 channels per cog of PWM 
  signals.  More than one cog may be launched, so for example, if 5 
  signals are desired, use 3 cogs for up to 6 channels.
 
  @version 0.5 
  
  @par Help Improve this Library
  Please submit bug reports, suggestions, and improvements to this code to
  editor@parallax.com.
*/

#ifndef PWM2CH_H
#define PWM2CH_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
#endif // DOXYGEN_SHOULD_SKIP_THIS


typedef pwm2ch_t pwm2ch;

  

/**
  @brief Start PWM process in another cog.  
  
  @param cycleMicroseconds The number of microseconds each cycle
  lasts. 
  
  @returns *device A pointer that should be stored in a 
  pwm2ch *variable and used as a process ID in other pwm2ch_... 
  function calls.
*/
pwm2ch * pwm2ch_start(unsigned int cycleMicroseconds);

/**
  @brief Set a PWM signal's high time.
 
  @param *device The pwm2ch pointer/process ID returned by pwm2ch_start.
 
  @param pin The pin to send the PWM signal. 
 
  @param channel 0 or 1.
  
  @param dacVal For PWM, use 0 to cycleMicroseconds.  To shut down a 
  channel and set the I/O pin to input, use -1.
*/
void pwm2ch_set(pwm2ch *device, int pin, int channel, int tHigh);

/**
  @brief Shut down pwm2ch process and reclaim cog and I/O pins for other
  uses.
 
  @param *device The pwm2ch pointer/process ID returned by pwm2ch_start.
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
