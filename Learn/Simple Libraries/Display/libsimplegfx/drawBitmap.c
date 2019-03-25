/*
 * @file drawBitmap.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This is a helper-library that allows the Propeller Multicore Microcontroller to 
 * draw text, shapes, and bitmap files on various screens and displays.
 *
 * @detail This helper-library allows the Propeller Multicore Microcontroller to 
 * draw pixels, lines, circles, recatngles, rounded rectagles, triangles, formatted text 
 * in multiple fonts, bitmap images stored on an SD card on various screens and displays. 
 * At Parallax, we would like to thank Adafruit Industries as parts of this library 
 * were dervied from the Adafruit GFX library for Arduino.  Please submit bug reports, 
 * suggestions, and improvements to this code to editor@parallax.com.
 * 
 * @note This library should not be called on its own - it is called by If fonts are installed, they occupy EEPROM addresses 40576 to 63359.
 */

#include "simplegfx.h"

// Draw an image (bitmap) at the specified (x,y) position

void drawBitmap(screen_t *dev, char *imgdir, int x, int y) {

  int x0, y0;
  
  char imgdat[dev->width * 2];                      // Buffer for characters
  FILE* fp = fopen(imgdir, "r");                    // Open file for reading

  fread(imgdat, 1, 30, fp);                         // Read 30 characters
  
  int img_width = (imgdat[18] << 1);                // get the image width in pixels
  int img_height = imgdat[22];                      // get the image height in pixels
  if(img_width > (dev->width * 2) || 
      img_height > (dev->height * 2)) return;       // image is too large for the function to display it
  int img_offset = imgdat[10];                      // find the byte (pointer) where the image data begins
  fread(imgdat, 1, img_offset - 30, fp);            // advance the file pointer to the image data by reading it
  
  int k = 0;
  while(k < img_height) {
    fread(imgdat, 1, img_width, fp);
    int y0 = y + img_height - 1 - k;
    if(y0 >= 0 && y0 < dev->height) {
      int j = 1;
      while(j < img_width) {
        x0 = (j >> 1) + x;
        while(x0 < 0) j+= 2;
        while(x0 < dev->width) {
          int c = (imgdat[j] << 8) | imgdat[j-1];
          drawPixel(dev, x0, y0, c);
          j += 2;
          if(j > img_width) break;
        }
        j += 2;
      }
    }
    k++;
  }
   
  fclose(fp);                                 // Close the file  
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

