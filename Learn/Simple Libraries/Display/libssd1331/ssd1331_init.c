/*
 * @file ssd1331_init.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2016.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display bitmap driver, see ssd1331_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "ssd1331.h"
#include "simpletools.h"



screen_t* ssd1331_init(char sdi, char sclk, char cs, char rs, char rst, int _width, int _height) {
  
  screen_t* dev = (screen_t*) malloc(sizeof(screen_t));
  memset(dev, 0, sizeof(screen_t));

  dev->color_depth = 16;  // Set the color depth 16 bits

  dev->dev_id =     cs;
  dev->dc_pin =     rs;
  dev->sdi_pin =    sdi;
  dev->clk_pin =    sclk;
  dev->rst_pin =    rst;
  
  dev->rotation =   2;  
  dev->width =      _width;
  dev->height =     _height;
  dev->text_size =  1;
  dev->text_wrap =  1;
  dev->text_color = WHITE;
  dev->bg_color =   WHITE;
  
  dev->deviceDrawPixel =        ssd1331_drawPixel;
  dev->deviceDrawLine =         ssd1331_drawLine;       // Use if device has hardware accelerated line drawing (otherwise 0)
  dev->deviceDrawFastHLine =    ssd1331_drawFastHLine;
  dev->deviceDrawFastVLine =    ssd1331_drawFastVLine;
  dev->deviceFillRect =         ssd1331_fillRect;       // Use if device has hardware accelerated filled rectagle drawing (otherwise 0)
  dev->deviceCopyRect =         ssd1331_copy;

  dev->deviceInterface =        INTF_SPI_NO_BUFFER;     // interface type (bit 1) (1-i2c/0-SPI) and buffer (bit 0) (0-yes/1-no)

  dev->deviceClearDisplay =     ssd1331_clearDisplay;
  dev->deviceResetDisplay =     ssd1331_resetDisplay;
  dev->deviceInvertDisplay =    ssd1331_invertDisplay;
  dev->deviceSleepWakeDisplay = ssd1331_sleepWakeDisplay;

  // set pin directions
  set_direction(sclk, 1);
  set_direction(sdi, 1);

  // CS low so it'll listen to us
  low(cs);

  // Default to Byte mode
  low(rs);

  // Reset the display
  ssd1331_resetDisplay(dev);
  
  int mask_cs =  (1 << cs);
  int mask_sdi = (1 << sdi);
  int mask_clk = (1 << sclk);
  int mask_dc =  (1 << rs);

  ssd1331_writeLockSet(dev->dev_id);
  
  // Initialization Sequence
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DISPLAYOFF, 0);     // 0xAE
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SETREMAP, 0);       // 0xA0
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x72, 0);                       // RGB Color
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_STARTLINE, 0);      // 0xA1
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x00, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DISPLAYOFFSET, 0);  // 0xA2
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x00, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_NORMALDISPLAY, 0);  // 0xA4
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SETMULTIPLEX, 0);   // 0xA8
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x3F, 0);                       // 0x3F 1/64 duty
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SETMASTER, 0);      // 0xAD
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x8E, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_POWERMODE, 0);      // 0xB0
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x0B, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_PRECHARGE, 0);      // 0xB1
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x31, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_CLOCKDIV, 0);       // 0xB3
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0xF0, 0);                       // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_PRECHARGEA, 0);     // 0x8A
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x64, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_PRECHARGEB, 0);     // 0x8B
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x78, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_PRECHARGEA, 0);     // 0x8C
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x64, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_PRECHARGELEVEL, 0); // 0xBB
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x3A, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_VCOMH, 0);          // 0xBE
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x3E, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_MASTERCURRENT, 0);  // 0x87
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x06, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_CONTRASTA, 0);      // 0x81
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x91, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_CONTRASTB, 0);      // 0x82
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x50, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_CONTRASTC, 0);      // 0x83
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x7D, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DISPLAYON, 0);      //--turn on oled panel

  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_CLEAR, 0);          // Clear the screen
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x00, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0x00, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, _width - 1, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, _height - 1, 0);
  
  ssd1331_writeLockClear(dev->dev_id);
  
  pause(25);
  
  return dev;
}


void ssd1331_resetDisplay(screen_t* dev) {
  // Toggle RST low to reset if pin is defined
  if(dev->rst_pin >= 0 && dev->rst_pin < 32) {
    high(dev->rst_pin);
    pause(100);
    low(dev->rst_pin);
    pause(100);
    high(dev->rst_pin);
    pause(100);
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
