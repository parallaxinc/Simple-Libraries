/**
  @file dac2ch.h
 
  @author Andy Lindsay
 
  @copyright
  Copyright (C) Parallax, Inc. 2018. All Rights MIT Licensed.
 
  @brief Functions for up to 2 channels per cog of duty modulated 
  signals for D/A conversion through a low pass filter.  More than
  one cog may be launched, so for example, if 5 signals are desired, 
  use 3 cogs for up to 6 channels.
 
  @version 0.5 
  
  @par Help Improve this Library
  Please submit bug reports, suggestions, and improvements to this code to
  editor@parallax.com.
*/

#ifndef DAC2CH_H
#define DAC2CH_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct dac2ch_st {
  volatile unsigned int dacCtrBits;
  volatile unsigned int dacBitX;
  volatile unsigned int ctra; 
  volatile unsigned int ctrb;
  volatile unsigned int frqa;
  volatile unsigned int frqb; 
  volatile unsigned int pin;
  volatile int dac2chCog;
  int dac2chStack[100];
} dac2ch_t;
#endif // DOXYGEN_SHOULD_SKIP_THIS


typedef dac2ch_t dac2ch;

/**
  @brief Start duty modulation process in another cog for D/A 
  conversion through a low pass filter.  
  
  @param bits Number of bits for the D/A converter.  The number of
  voltage settings will be 2^bits.  For example, setting bits to 8
  gives 2^8 = 256 voltage settings, from 0 -> 0 V to 255 -> 3.287 V 
  on a 3.3 V scale. 
  
  @returns *device A pointer that should be stored in a 
  dac2ch *variable and used as a process ID in other dac2ch_... 
  function calls.
*/
dac2ch * dac2ch_start(int bits);

/**
  @brief Set a DAC signal's level.
 
  @param *device The dac2ch pointer/process ID returned by dac2ch_start.
 
  @param pin The pin to send the duty modulated DAC signal. 
 
  @param channel 0 or 1.
  
  @param dacVal For D/A, use 0 to (2^bits) - 1.  For example, for 
  9 bits, that would be 0 to 511.  To shut down a channel and set 
  the I/O pin to input, use -1.
*/
void dac2ch_set(dac2ch *device, int pin, int channel, int dacVal);

/**
  @brief Shut down dac2ch process and reclaim cog and I/O pins for other
  uses.
 
  @param *device The dac2ch pointer/process ID returned by dac2ch_start.
*/
void dac2ch_stop(dac2ch *device);


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
  TERMS OF USE: MIT License
 
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/
