/*
 * @file il3820_update.c
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


void il3820_updateDisplay(screen_t *dev)
{
  il3820_writeLockSet(dev->dev_id);

  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);
  
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_RAM_X_ADDRESS_POSITION, 0);
  
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, ((dev->width - 1) >> 3) & 0xFF, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_RAM_Y_ADDRESS_POSITION, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, (dev->height - 1) & 0xFF, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, ((dev->height - 1) >> 3) & 0xFF, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_RAM_X_ADDRESS_COUNTER, 0);
  
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_RAM_Y_ADDRESS_COUNTER, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 1);

  // TODO: is this needed?
  while (input(dev->status_pin) == 1) pause(10);        //0: idle, 1: busy

  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_WRITE_RAM, 0);
  
  OUTA |= mask_dc;                                      // force data mode
  il3820_spiWriteBytes(mask_cs, mask_sdi, mask_clk, mask_dc, dev->image_ptr, dev->image_size);
  
  // Update display
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_DISPLAY_UPDATE_2, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0xC4, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_MASTER_ACTIVATION, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_TERMINATE_FRAME_READ_WRITE, 0);
  
  il3820_writeLockClear(dev->dev_id);
  
  while (input(dev->status_pin) == 1) pause(2);        //0: idle, 1: busy
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
