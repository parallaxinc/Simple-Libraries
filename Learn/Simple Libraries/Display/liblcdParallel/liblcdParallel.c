/**
 * @file liblcdParallel.c
 *
 * @author Matthew Matz, Jeff Martin
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2018. All Rights MIT Licensed.
 *
 * @brief Display driver for character LCD screens based on Hitachi HD44780 
 * (or compatible) chipsets, which are found in most text-based LCDs. 
 * The library works with either 4 or 8 data lines in addition
 * to the rs, and enable lines.
 */



#include "simpletools.h"                      // Include simple tools
#include "lcdParallel.h"
#include "abvolts.h"

lcdParallel *screen;

// ------ Main Program ------
int main() {
  da_init(26, 27);
  da_out(0, 48);
  high(24);
  int secs = 0;

  // set up the LCD's mode, number of columns & rows, and pins:
  screen = lcdParallel_init(16, 2, 8, 4, 5, 6, 7, 8, 9);

  // Print a message to the LCD.
  lcdParallel_print(screen, "Hello, World!");
  
  char smiley[8] = {
    0b10001,
    0b10001,
    0b00000,
    0b00100,
    0b00000,
    0b10001,
    0b01110
  };

  lcdParallel_createChar(screen, 0, smiley);

  while(1) {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcdParallel_setCursor(screen, 0, 1);
    // print the number of seconds since reset:
    lcdParallel_print(screen, "%d ", secs);
    lcdParallel_writeChar(screen, 0);
    secs++;
    pause(1000);
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
