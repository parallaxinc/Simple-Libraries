/*
 * @file oledc_drawCharMedium.c
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

char oledc_font_med[2090];

void oledc_drawCharMedium(int x, int y, unsigned char c, unsigned int color, unsigned int bg) 
{
  c -= 33;
  for (char i = 0; i < 22; i += 2 ) 
  {
    int li;
    
    if (i < 22) li = (oledc_font_med[c * 22 + i] << 8) | oledc_font_med[c * 22 + i + 1];
    else        li = 0x0;

    for (char j = 0; j < 16; j++, li >>= 1) 
    {
      if (li & 0x1)          oledc_drawPixel(x + i / 2, y + j, color);
      else if (bg != color)  oledc_drawPixel(x + i / 2, y + j, bg);
    }
    
    if (bg != color)
    {
      oledc_drawFastVLine(x + 11, y, 17, bg);
      oledc_drawFastHLine(x, y + 16, 11, bg);
    }      
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
