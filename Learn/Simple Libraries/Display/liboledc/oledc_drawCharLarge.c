/*
 * @file oledc_drawCharLarge.c
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

char font_lg_zeroMap[];
char font_lg_index[];
char oled_font_lg[];

static char current_character[51] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void oledc_drawCharLarge(int x, int y, unsigned char c, unsigned int color, unsigned int bg) 
{
  int offset = 0;
  int idx;
  char li;
  int ctr = 0;
  
  for(int i = 1; i < (c-32); i++) offset += font_lg_index[i];   // sum the index to find the offset
  
  for(int k = 1; k < 8; k++)
  {
    li = font_lg_zeroMap[7*(c-33) + k - 1];
    for(int j = 0; j < 8; j++) 
    {
      ctr++;
      char t = li & (1 << (7-j));
      if((t > 0) && ctr < 52)
      {
        current_character[ctr] = oled_font_lg[offset];
        offset++;
      } else if(ctr < 52) {
        current_character[ctr] = 0x00;
      }
    }                 
  }    

  for (char i = 1; i < 52; i += 3 ) 
  {
    int li;
    if (i < 51) li = (current_character[i] << 16) | (current_character[i + 1] << 8) | current_character[i + 2];
    else        li = 0x0;

    for (char j = 0; j < 23; j++, li >>= 1) 
    {
      if (li & 0x1)          oledc_drawPixel(x + i / 3, y + j, color);
      else if (bg != color)  oledc_drawPixel(x + i / 3, y + j, bg);
    }
    
    if (bg != color)
    {
      oledc_drawFastVLine(x + 17, y, 24, bg);
      oledc_drawFastHLine(x, y + 23, 17, bg);
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
