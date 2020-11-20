/*
 * @file ssd1331_drawLine.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display bitmap driver, see ssd1331_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "ssd1331.h"


void ssd1331_drawLine(screen_t* dev, int x0, int y0, int x1, int y1, int color) {
  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  ssd1331_writeLockSet(dev->dev_id);

  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DRAWLINE, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, x0, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, y0, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, x1, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, y1, 0);

  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, (color >> 11) << 1,  0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, (color >> 5) & 0x3F, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, (color << 1) & 0x3F, 0);

  //TODO: is this needed?
  int _tMark = CNT + (CLKFREQ / 100000);
  while (_tMark > CNT);                         // Wait for system clock target

  ssd1331_writeLockClear(dev->dev_id);
}

void ssd1331_drawFastVLine(screen_t* dev, int x, int y, int w, int color) {
  ssd1331_drawLine(dev, x, y, x, y + w - 1, color);
}

void ssd1331_drawFastHLine(screen_t* dev, int x, int y, int h, int color) {
  ssd1331_drawLine(dev, x, y, x + h - 1, y, color);
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