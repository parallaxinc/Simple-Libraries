/*
 * @file setText.c
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


void setCursor(screen_t *dev, int x, int y, char size) {
  if (size < 1) {
    dev->cursor_x = x;
    dev->cursor_y = y;
  } else {
    dev->cursor_x = x * 6 * size;
    dev->cursor_y = y * (size << 3);
  }
}

void setTextSize(screen_t *dev, char s) {
  if(dev->font[0] == 0) 
  {
    dev->text_size = 1;
  } else {
    dev->text_size = s;
    if(s < 1) dev->text_size = 1;
    if(s > 3) dev->text_size = 3;
  }    
}

void setTextColor(screen_t *dev, int c) {
  dev->text_color = c;
}

void setBgColor(screen_t *dev, int c) {
  dev->bg_color = c;
}

void setTextWrap(screen_t *dev, char w) {
  dev->text_wrap = !(!w);   // Force it to be a boolean
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
