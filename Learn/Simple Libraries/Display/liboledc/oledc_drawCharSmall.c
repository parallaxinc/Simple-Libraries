/*
 * @file oledc_drawCharSmall.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2016.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display driver component, see oledc_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "oledc.h"

const char oledc_font_sm[] = {
  0x00, 0x00, 0x5F, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x07, 0x00,
  0x14, 0x7F, 0x14, 0x7F, 0x14,
  0x24, 0x2A, 0x7F, 0x2A, 0x12,
  0x23, 0x13, 0x08, 0x64, 0x62,
  0x36, 0x49, 0x56, 0x20, 0x50,
  0x00, 0x08, 0x07, 0x03, 0x00,
  0x00, 0x1C, 0x22, 0x41, 0x00,
  0x00, 0x41, 0x22, 0x1C, 0x00,
  0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
  0x08, 0x08, 0x3E, 0x08, 0x08,
  0x00, 0x80, 0x70, 0x30, 0x00,
  0x08, 0x08, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x60, 0x60, 0x00,
  0x20, 0x10, 0x08, 0x04, 0x02,
  0x3E, 0x51, 0x49, 0x45, 0x3E,
  0x00, 0x42, 0x7F, 0x40, 0x00,
  0x72, 0x49, 0x49, 0x49, 0x46,
  0x21, 0x41, 0x49, 0x4D, 0x33,
  0x18, 0x14, 0x12, 0x7F, 0x10,
  0x27, 0x45, 0x45, 0x45, 0x39,
  0x3C, 0x4A, 0x49, 0x49, 0x31,
  0x41, 0x21, 0x11, 0x09, 0x07,
  0x36, 0x49, 0x49, 0x49, 0x36,
  0x46, 0x49, 0x49, 0x29, 0x1E,
  0x00, 0x00, 0x14, 0x00, 0x00,
  0x00, 0x40, 0x34, 0x00, 0x00,
  0x00, 0x08, 0x14, 0x22, 0x41,
  0x14, 0x14, 0x14, 0x14, 0x14,
  0x00, 0x41, 0x22, 0x14, 0x08,
  0x02, 0x01, 0x59, 0x09, 0x06,
  0x3E, 0x41, 0x5D, 0x59, 0x4E,
  0x7C, 0x12, 0x11, 0x12, 0x7C,
  0x7F, 0x49, 0x49, 0x49, 0x36,
  0x3E, 0x41, 0x41, 0x41, 0x22,
  0x7F, 0x41, 0x41, 0x41, 0x3E,
  0x7F, 0x49, 0x49, 0x49, 0x41,
  0x7F, 0x09, 0x09, 0x09, 0x01,
  0x3E, 0x41, 0x41, 0x51, 0x73,
  0x7F, 0x08, 0x08, 0x08, 0x7F,
  0x00, 0x41, 0x7F, 0x41, 0x00,
  0x20, 0x40, 0x41, 0x3F, 0x01,
  0x7F, 0x08, 0x14, 0x22, 0x41,
  0x7F, 0x40, 0x40, 0x40, 0x40,
  0x7F, 0x02, 0x1C, 0x02, 0x7F,
  0x7F, 0x04, 0x08, 0x10, 0x7F,
  0x3E, 0x41, 0x41, 0x41, 0x3E,
  0x7F, 0x09, 0x09, 0x09, 0x06,
  0x3E, 0x41, 0x51, 0x21, 0x5E,
  0x7F, 0x09, 0x19, 0x29, 0x46,
  0x26, 0x49, 0x49, 0x49, 0x32,
  0x03, 0x01, 0x7F, 0x01, 0x03,
  0x3F, 0x40, 0x40, 0x40, 0x3F,
  0x1F, 0x20, 0x40, 0x20, 0x1F,
  0x3F, 0x40, 0x38, 0x40, 0x3F,
  0x63, 0x14, 0x08, 0x14, 0x63,
  0x03, 0x04, 0x78, 0x04, 0x03,
  0x61, 0x59, 0x49, 0x4D, 0x43,
  0x00, 0x7F, 0x41, 0x41, 0x41,
  0x02, 0x04, 0x08, 0x10, 0x20,
  0x00, 0x41, 0x41, 0x41, 0x7F,
  0x04, 0x02, 0x01, 0x02, 0x04,
  0x40, 0x40, 0x40, 0x40, 0x40,
  0x00, 0x03, 0x07, 0x08, 0x00,
  0x20, 0x54, 0x54, 0x78, 0x40,
  0x7F, 0x28, 0x44, 0x44, 0x38,
  0x38, 0x44, 0x44, 0x44, 0x28,
  0x38, 0x44, 0x44, 0x28, 0x7F,
  0x38, 0x54, 0x54, 0x54, 0x18,
  0x00, 0x08, 0x7E, 0x09, 0x02,
  0x18, 0xA4, 0xA4, 0x9C, 0x78,
  0x7F, 0x08, 0x04, 0x04, 0x78,
  0x00, 0x44, 0x7D, 0x40, 0x00,
  0x20, 0x40, 0x40, 0x3D, 0x00,
  0x7F, 0x10, 0x28, 0x44, 0x00,
  0x00, 0x41, 0x7F, 0x40, 0x00,
  0x7C, 0x04, 0x78, 0x04, 0x78,
  0x7C, 0x08, 0x04, 0x04, 0x78,
  0x38, 0x44, 0x44, 0x44, 0x38,
  0xFC, 0x18, 0x24, 0x24, 0x18,
  0x18, 0x24, 0x24, 0x18, 0xFC,
  0x7C, 0x08, 0x04, 0x04, 0x08,
  0x48, 0x54, 0x54, 0x54, 0x24,
  0x04, 0x04, 0x3F, 0x44, 0x24,
  0x3C, 0x40, 0x40, 0x20, 0x7C,
  0x1C, 0x20, 0x40, 0x20, 0x1C,
  0x3C, 0x40, 0x30, 0x40, 0x3C,
  0x44, 0x28, 0x10, 0x28, 0x44,
  0x4C, 0x90, 0x90, 0x90, 0x7C,
  0x44, 0x64, 0x54, 0x4C, 0x44,
  0x00, 0x08, 0x36, 0x41, 0x00,
  0x00, 0x00, 0x77, 0x00, 0x00,
  0x00, 0x41, 0x36, 0x08, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x02,
};


void oledc_drawCharSmall(int x, int y, unsigned char c, unsigned int color, unsigned int bg) 
{
  c -= 33;
  for (char i = 0; i < 6; i++ ) 
  {
    int li;

    if (i < 5) li = oledc_font_sm[c * 5 + i];
    else       li = 0x0;

    for (char j = 0; j < 8; j++, li >>= 1) 
    {
      if (li & 0x1)          oledc_drawPixel(x + i, y + j, color);
      else if (bg != color)  oledc_drawPixel(x + i, y + j, bg);
    }
    
    if (bg != color)
    {
      oledc_drawFastVLine(x + 6, y, 8, bg);
      oledc_drawFastHLine(x, y + 8, 7, bg);
    }          
  }
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
