/*
 * @file drawNumber.c
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



void drawNumber(screen_t *dev, float d, int r) {
  int stringLen = 1;
  char bffr[64];
  int temp_d;
  int isNegative = 0;

  if(d < 0) {
    d = -d;
    isNegative = 1;
  }    

  if (r == 0) r = -10;
  if (r < 0) {
    r = -r;
    temp_d = (int) d;

    while ((int)temp_d / r != 0) {
      temp_d = (int)temp_d / r;
      stringLen++;
    }
    temp_d = d;
    bffr[stringLen] = 0;
    
    do {
      int theNumber = (temp_d % r);
      if (theNumber > 9) theNumber = theNumber + 7;
      bffr[stringLen - 1] = theNumber + '0';
      temp_d = (int) temp_d / r;
    } while (stringLen--);

  } else {
    
    int t = 1;
    for (int p = 0; p < r; p++) t *= 10;
    r = 10;
    int i_part = (int) d;
    int d_part = ((int) (d * t + 0.5)) - (i_part * t);
    int d_place;

    temp_d = (int) d;

    while ((int)temp_d / r != 0) {
      temp_d = (int)temp_d / r;
      stringLen++;
    }
    temp_d = d;
    d_place = stringLen;
    d_place++;
    
    do {
      int theNumber = (temp_d % r);
      bffr[stringLen - 1] = theNumber + '0';
      temp_d = (int) temp_d / r;
    } while (stringLen--);

    temp_d = (int) d_part;
    int stringLen = 1;

    while ((int)temp_d / r != 0) {
      temp_d = (int)temp_d / r;
      stringLen++;
    }
    temp_d = d_part;
    bffr[stringLen + d_place] = 0;
    
    do {
      int theNumber = (temp_d % r);
      bffr[stringLen - 1 + d_place] = theNumber + '0';
      temp_d = (int) temp_d / r;
    } while (stringLen--);
    bffr[d_place - 1] = '.';
  }
  
  if(isNegative) {
    int l = strlen(bffr);
    bffr[l + 2] = 0;
    for(int m = l; m >= 0; m--) bffr[m+1] = bffr[m];
    bffr[0] = '-';
  }    
  
  if (r >= 0 && isNegative && !(r == 10)) {
    drawText(dev, "Err");    
  } else {
    drawText(dev, bffr);
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
