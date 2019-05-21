/*
 * @file il3820_spiWrite.c
 *
 * @author Matthew Matz & Roy Eltham
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Waveshare ePaper display bitmap driver, see il3820_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "il3820.h"
#include <propeller.h>

// ------------------- low level pin interface --------------------
static char _writeLock = 0;

void il3820_spiWrite(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc) {
  
  // Conditionally set _rs (Source: https://graphics.stanford.edu/~seander/bithacks.html)
  unsigned int mask = (-(dc) ^ OUTA) & mask_dc;  
  OUTA ^= mask;
   
  OUTA &= ~mask_cs;
  OUTA &= ~mask_clk;                                        // Pin output state to low
  DIRA |= mask_clk;                                         // Pin direction to output

  for (int i = 7; i >= 0 ; i--) {
    if ((c >> i) & 1)  OUTA |= mask_sdi;
    else               OUTA &= (~mask_sdi);
    OUTA ^= mask_clk;
    OUTA ^= mask_clk;
  }
  OUTA |= mask_cs;
}


__attribute__((fcache))                    // allows function to run directly from cog ram, 10x+ speed increase
void il3820_spiWriteBytes(int mask_cs, int mask_sdi, int mask_clk, const unsigned char* data, int numBytes) {
    OUTA &= ~mask_cs;
    OUTA &= ~mask_clk;                                        // Pin output state to low
    DIRA |= mask_clk;                                         // Pin direction to output

    for (int j = 0; j < numBytes; j++) {
        for (int i = 7; i >= 0; i--) {
            if ((data[j] >> i) & 1)  OUTA |= mask_sdi;
            else                     OUTA &= (~mask_sdi);
            OUTA ^= mask_clk;
            OUTA ^= mask_clk;
        }
    }
    OUTA |= mask_cs;
}


char il3820_writeLock() {
  return _writeLock;
}  

void il3820_writeLockSet(char devId) {
  while(_writeLock);
  _writeLock = devId;
}  

void il3820_writeLockClear(char devId) {
  if (_writeLock == devId) {
    _writeLock = 0;
  }    
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
