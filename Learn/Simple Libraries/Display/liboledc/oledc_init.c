/*
 * @file oledc_init.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2016.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display bitmap driver, see oledc_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "oledc.h"

char _cs, _rs, _rst, _sid, _sclk;

char TFTROTATION;
char TFTINVERTED = 0;
int textsize = 1;
char TFTSCROLLING = 0;
unsigned int textcolor = 0xFFFF;
unsigned int textbgcolor = 0xFFFF;
char wrap = 1;
int cursor_y = 0;
int cursor_x = 0;
int _width, _height;


void oledc_init(char cs, char rs, char sid, char sclk, char rst, char screen_rotation) {
  
  _cs = cs;
  _rs = rs;
  _sid = sid;
  _sclk = sclk;
  _rst = rst;
  
  // set pin directions
  DIRA |= 1 << _rs;
  DIRA |= 1 << _sclk;
  DIRA |= 1 << _sid;

  // Toggle RST low to reset; CS low so it'll listen to us
  OUTA &= ~(1 << _cs);
  DIRA |= 1 << _cs;

  OUTA |= 1 << _rst;
  DIRA |= 1 << _rst;
  waitcnt(CLKFREQ / 2 + CNT);                      // Wait for system clock target
  OUTA &= ~(1 << _rst);
  waitcnt(CLKFREQ / 2 + CNT);                      // Wait for system clock target
  OUTA |= 1 << _rst;
  waitcnt(CLKFREQ / 2 + CNT);                      // Wait for system clock target

  // Initialization Sequence
  oledc_writeCommand(SSD1331_CMD_DISPLAYOFF);    // 0xAE
  oledc_writeCommand(SSD1331_CMD_SETREMAP);  // 0xA0
  oledc_writeCommand(0x72);        // RGB Color
  oledc_writeCommand(SSD1331_CMD_STARTLINE);   // 0xA1
  oledc_writeCommand(0x0);
  oledc_writeCommand(SSD1331_CMD_DISPLAYOFFSET);   // 0xA2
  oledc_writeCommand(0x0);
  oledc_writeCommand(SSD1331_CMD_NORMALDISPLAY);   // 0xA4
  oledc_writeCommand(SSD1331_CMD_SETMULTIPLEX);  // 0xA8
  oledc_writeCommand(0x3F);        // 0x3F 1/64 duty
  oledc_writeCommand(SSD1331_CMD_SETMASTER);   // 0xAD
  oledc_writeCommand(0x8E);
  oledc_writeCommand(SSD1331_CMD_POWERMODE);   // 0xB0
  oledc_writeCommand(0x0B);
  oledc_writeCommand(SSD1331_CMD_PRECHARGE);   // 0xB1
  oledc_writeCommand(0x31);
  oledc_writeCommand(SSD1331_CMD_CLOCKDIV);    // 0xB3
  oledc_writeCommand(0xF0);  // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
  oledc_writeCommand(SSD1331_CMD_PRECHARGEA);    // 0x8A
  oledc_writeCommand(0x64);
  oledc_writeCommand(SSD1331_CMD_PRECHARGEB);    // 0x8B
  oledc_writeCommand(0x78);
  oledc_writeCommand(SSD1331_CMD_PRECHARGEA);    // 0x8C
  oledc_writeCommand(0x64);
  oledc_writeCommand(SSD1331_CMD_PRECHARGELEVEL);    // 0xBB
  oledc_writeCommand(0x3A);
  oledc_writeCommand(SSD1331_CMD_VCOMH);     // 0xBE
  oledc_writeCommand(0x3E);
  oledc_writeCommand(SSD1331_CMD_MASTERCURRENT);   // 0x87
  oledc_writeCommand(0x06);
  oledc_writeCommand(SSD1331_CMD_CONTRASTA);   // 0x81
  oledc_writeCommand(0x91);
  oledc_writeCommand(SSD1331_CMD_CONTRASTB);   // 0x82
  oledc_writeCommand(0x50);
  oledc_writeCommand(SSD1331_CMD_CONTRASTC);   // 0x83
  oledc_writeCommand(0x7D);
  oledc_writeCommand(SSD1331_CMD_DISPLAYON); //--turn on oled panel
  
  oledc_setRotation(screen_rotation);
  TFTROTATION = screen_rotation & 3;
  
  oledc_clear(0,0,_width,_height);
  
}

// Parts of this file are from the Adafruit GFX arduino library

/***************************************************
  This is a library for the 0.96" 16-bit Color OLED with SSD1331 driver chip
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/684
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

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
