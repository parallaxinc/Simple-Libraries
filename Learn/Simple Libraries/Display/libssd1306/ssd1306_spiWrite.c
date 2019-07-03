/*
 * @file ssd1306_spiWrite.c
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


#include "ssd1306.h"
#include <propeller.h>

// ------------------- low level pin interface --------------------
static char _writeLock = 0;

void ssd1306_write(screen_t* dev, unsigned int c, char dc) {
  if (dev->deviceInterface & 1) {
    char theChar[] = {0, 0};
    theChar[0] = (c & 255);
    
    // TODO: check for busy line here?
    i2c_out(dev->deviceBus, dev->dev_id, (dc == 0 ? 0x00 : 0x40), 1, (unsigned char *) theChar, 1);
    
  } else { 
    int mask_cs =  (1 << dev->dev_id);
    int mask_sdi = (1 << dev->sdi_pin);
    int mask_clk = (1 << dev->clk_pin);
    int mask_dc =  (1 << dev->dc_pin);

    ssd1306_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, (char) c, dc);
  }        
}


void ssd1306_writeBytes(screen_t* dev, unsigned char *c, int n, char dc) {
  if (dev->deviceInterface & 1) {    
    
    // TODO: check for busy line here?
    i2c_out(dev->deviceBus, dev->dev_id, (dc == 0 ? 0x00 : 0x40), 1, c, n);

  } else {   
    int mask_cs =  (1 << dev->dev_id);
    int mask_sdi = (1 << dev->sdi_pin);
    int mask_clk = (1 << dev->clk_pin);
    int mask_dc =  (1 << dev->dc_pin);
    
    ssd1306_spiWriteBytes(mask_cs, mask_sdi, mask_clk, mask_dc, c, dc, n);
  }        
}


__attribute__((fcache))                    // allows function to run directly from cog ram, 10x+ speed increase
void ssd1306_spiWrite(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, char c, char dc) {
  
  // Conditionally set data/command pin (Source: https://graphics.stanford.edu/~seander/bithacks.html)
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
void ssd1306_spiWriteBytes(int mask_cs, int mask_sdi, int mask_clk, int mask_dc, const unsigned char* data, char dc, int n) {

  // Conditionally set data/command pin
  unsigned int mask = (-(dc) ^ OUTA) & mask_dc;  
  OUTA ^= mask;

  OUTA &= ~mask_cs;
  OUTA &= ~mask_clk;                                        // Pin output state to low
  DIRA |= mask_clk;                                         // Pin direction to output

  for (int j = 0; j < n; j++) {
      for (int i = 7; i >= 0; i--) {
          if ((data[j] >> i) & 1)  OUTA |= mask_sdi;
          else                     OUTA &= (~mask_sdi);
          OUTA ^= mask_clk;
          OUTA ^= mask_clk;
      }
  }
  OUTA |= mask_cs;
}


char ssd1306_writeLock() {
  return _writeLock;
}  

void ssd1306_writeLockSet(char devId) {
  while(_writeLock);
  _writeLock = devId;
}  

void ssd1306_writeLockClear(char devId) {
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