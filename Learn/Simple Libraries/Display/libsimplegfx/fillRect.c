/*
 * @file fillRect.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This is a driver that allows the Propeller Multicore Microcontroller to 
 * draw text, shapes, and bitmap files on various screens and displays.
 *
 * @detail This helper-library allows the Propeller Multicore Microcontroller to 
 * draw pixels, lines, circles, recatngles, rounded rectagles, triangles, formatted text 
 * in multiple fonts, bitmap images stored on an SD card on various screens and displays. 
 * At Parallax, we would like to thank Adafruit Industries as parts of this library 
 * were dervied from the Adafruit GFX library for Arduino.  Please submit bug reports, 
 * suggestions, and improvements to this code to editor@parallax.com.
 * 
 * @note If fonts are installed, they occupy EEPROM addresses 40576 to 63359.
 */


#include "simplegfx.h"


// Draw a filled rectangle
void fillRect(screen_t *dev, int x, int y, int w, int h, int color) {
  if (dev->deviceFillRect) {
    int dh = getDisplayHeight(dev);
    int dw = getDisplayWidth(dev);
    if((x >= -w) && (x < dw) && 
        (y >= -h) && (y < dh)) { // X & Y coord in bounds?
      if(y < 0) {                // Clip top
        h += y;
        y  = 0;
      }
      if((y + h) > dh) {         // Clip bottom
        h = (dh - y);
      }     
      if(x < 0) {                // Clip left
        w += x;
        x  = 0;
      }
      if((x + w) > dw) {         // Clip right
        w = (dw - x);
      }
      int x1 = x + w - 1;
      int y1 = y + h - 1;
      switch(dev->rotation) {
       case 0:
        dev->deviceFillRect(dev, x, y, x1, y1, color);
        break;
       case 1:
        dev->deviceFillRect(dev, dev->width - y1, x, dev->width - y, x1, color);
        break;
       case 2:
        dev->deviceFillRect(dev, dev->width - x1, dev->height - y1, dev->width - x, dev->height - y, color);
        break;
       case 3:
        dev->deviceFillRect(dev, y, dev->height - x1, y1, dev->height - x, color);
        break;
      }
    }    
  } else {     
    for (int idx = y; idx < y + h; idx++) {
      drawFastHLine(dev, x, idx, w, color);
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
