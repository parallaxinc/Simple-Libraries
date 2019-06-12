/*
 * @file drawRoundRect.c
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

void drawRoundRect(screen_t *dev, int x, int y, int w, int h, int r, int color) {
  int sMin = w;
  if(h < w) sMin = h;
  if(r >= sMin/2) r = sMin/2 - 1;
  
  // draw straight portions of the rectangle's sides
  int ll = 1 + (r * 2);
  drawFastHLine(dev, x + r,     y,         w - ll, color);
  drawFastHLine(dev, x + r,     y + h - 1, w - ll, color);
  drawFastVLine(dev, x,         y + r,     h - ll, color);
  drawFastVLine(dev, x + w - 1, y + r,     h - ll, color);

  // draw four corners
  drawCircleHelper(dev, x + r,         y + r,         r, 1, color);
  drawCircleHelper(dev, x + w - r - 1, y + r,         r, 2, color);
  drawCircleHelper(dev, x + w - r - 1, y + h - r - 1, r, 4, color);
  drawCircleHelper(dev, x + r,         y + h - r - 1, r, 8, color);
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
