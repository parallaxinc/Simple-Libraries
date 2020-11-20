/*
 * @file ssd1331_spiWrite.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display bitmap driver, see oledc_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "ssd1331.h"

// ------------------- low level pin interface --------------------
static char _writeLock;


__attribute__((fcache))                    // allows function to run directly from cog ram, 10x+ speed increase
void ssd1331_writeByte(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc) {
  
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

char ssd1331_writeLock() {
  return _writeLock;
}  

void ssd1331_writeLockSet(char devId) {
  while(_writeLock);
  _writeLock = devId;
}  

void ssd1331_writeLockClear(char devId) {
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