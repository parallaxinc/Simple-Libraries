/*
 * @file drawText.c
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


void drawText(screen_t *dev, char *myString) {
  for (int j = 0; j < strlen(myString); j++) {
    drawChar(dev, myString[j]);
  }
}


void drawChar(screen_t *dev, char c) {
  if (c == '\n' || c == '\r') {
    dev->cursor_y += (dev->text_size << 3);
    dev->cursor_x  = 0;
  } else {
    if (dev->text_wrap && ((dev->cursor_x + dev->text_size * 6) > getDisplayWidth(dev))) { // Heading off edge?
      dev->cursor_x  = 0;                     // Reset x to zero
      dev->cursor_y += (dev->text_size << 3); // Advance y one line
    }
    if (dev->text_wrap && ((dev->cursor_y + (dev->text_size << 3)) > getDisplayHeight(dev))) { // Heading below bottom?
      dev->cursor_x = 0;
      dev->cursor_y = 0;
    }
    
    if (dev->text_color != dev->bg_color) {
      fillRect(dev, dev->cursor_x, dev->cursor_y, dev->text_size * 6, dev->text_size << 3, dev->bg_color);
    }
    if (c < 32 || c > 126) { // draw unknown charachters as boxes
      drawRect(dev, dev->cursor_x + 1, dev->cursor_y + 1, dev->text_size * 6 - 2, (dev->text_size << 3) - 2, dev->text_color);
      if (dev->text_size > 1) drawRect(dev, dev->cursor_x + 2, dev->cursor_y + 2, dev->text_size * 6 - 4, (dev->text_size << 3) - 4, dev->text_color);
      if (dev->text_size > 2) drawRect(dev, dev->cursor_x + 3, dev->cursor_y + 3, dev->text_size * 6 - 6, (dev->text_size << 3) - 6, dev->text_color);
    } else { 
      if ((dev->cursor_x >= getDisplayWidth(dev))        || // Clip right
      (dev->cursor_y >= getDisplayHeight(dev))           || // Clip bottom
      ((dev->cursor_x + 6 * dev->text_size - 1) < 0)     || // Clip left
      ((dev->cursor_y + (dev->text_size << 3) - 1) < 0))       // Clip top
      return;

      if (c != 32) {
        if (dev->text_size < 2)  drawCharSmall(dev, c);
        if (dev->text_size == 2) drawCharMedium(dev, c);
        if (dev->text_size == 3) drawCharLarge(dev, c);
      }        
    }
    dev->cursor_x += dev->text_size * 6;
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
