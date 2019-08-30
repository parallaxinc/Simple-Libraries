/*
 * @file il3820_reset.c
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


/**
 *  @brief set the look-up table register
 */
const unsigned char lut_full_update[] = {
  0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69,
  0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00, 0x00,
  0xF8, 0xB4, 0x13, 0x51, 0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

// const unsigned char lut_partial_update[] = {
//   0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00,
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//   0x13, 0x14, 0x44, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
// };



void il3820_resetDisplay(screen_t *dev)
{
  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  il3820_writeLockSet(dev->dev_id);
  
  // reset
  low(dev->rst_pin);
  pause(200);
  high(dev->rst_pin);
  pause(200);

  // Initialization Sequence
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_DRIVER_OUTPUT, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, (dev->height - 1) & 0xFF, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, ((dev->height - 1) >> 8) & 0xFF, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0x00, 1);                     // GD = 0; SM = 0; TB = 0;
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_BOOSTER_SOFT_START, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0xD7, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0xD6, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0x9D, 1);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_WRITE_VCOM_REGISTER, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0xA8, 1);                     // VCOM 7C
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_DUMMY_LINE_PERIOD, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0x1A, 1);                     // 4 dummy lines per gate
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_SET_GATE_TIME, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0x08, 1);                     // 2us per line
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_DATA_ENTRY_MODE, 0);
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, 0x03, 1);                     // X increment; Y increment
  il3820_spiWrite(mask_cs, mask_sdi, mask_clk, mask_dc, IL3820_WRITE_LUT_REGISTER, 0);
  OUTA |= mask_dc;
  il3820_spiWriteBytes(mask_cs, mask_sdi, mask_clk, lut_full_update, 30);

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
