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
 * @note This library should not be called on its own - it is called by the display's
 * library.
 * If fonts are installed, they occupy EEPROM addresses 40576 to 63359.
 */

#include "simplegfx.h"


// Draw an image (bitmap) at the specified (x,y) position
void drawBitmap(screen_t *dev, char *imgdir, int x, int y) {
  
  char imgdat[32];                                  // Buffer for image data
  FILE* fp = fopen(imgdir, "r");                    // Open file for reading

  fread(imgdat, 1, 30, fp);                         // Read 30 characters
  
  int img_width = imgdat[18] | (imgdat[19] << 8) | (imgdat[20] << 16) | (imgdat[21] << 24);   // get the image width in pixels
  int img_height = imgdat[22] | (imgdat[23] << 8) | (imgdat[24] << 16) | (imgdat[25] << 24);  // get the image height in pixels
  int img_color_depth = ((imgdat[28] | (imgdat[29] << 8)) >> 3);                              // get the image height in bits, convert to bytes
  if (img_color_depth < 2 || img_color_depth > 4) return;                                     // exit if the image's color depth isn't supported
  
  //if(img_width > (dev->width << 1) || 
  //    img_height > (dev->height << 1)) return;     // image is too large for the function to display it
      
  int img_offset = imgdat[10];                      // find the byte (pointer) where the image data begins
  fseek(fp, img_offset - 30, SEEK_CUR);             // advance the file pointer to the image data
  
  int flip = 0;
  if (img_height < 0) {                             // If the height is negative, then tell the function to flip the image
    img_height *= -1;
    flip = 1;
  }    

  if (dev->color_depth != 1 && dev->color_depth != 16) return;  // exit if the screen's color depth isn't supported

  for (int k = img_height; k >= 0; k--) {
    int y0 = y;
    
    if (flip) y0 += img_height - 1 - k;             // Some bitmaps are drawn top-down
    else      y0 += k - 1;                          // Others are bottom-up
    
    if (y0 >= 0 && y0 < getDisplayHeight(dev)) {             // Is the pixel on screen?
      
      for(int j = 0; j < img_width; j++) {
        int x0 = j + x;
        
        if (x0 >= 0 && x0 < getDisplayWidth(dev)) {          // Is the pixel on screen?
          fread(imgdat, 1, img_color_depth, fp);
          
          if (img_color_depth == 2) {
            if (dev->color_depth == 16) 
              drawPixel(dev, x0, y0, (imgdat[1] << 8) | imgdat[0]);
            else 
              drawPixel(dev, x0, y0, ((((imgdat[1] >> 5) + (imgdat[1] & 0b111) + ((imgdat[0] >> 2) & 0b111)) > 10) ? 1 : 0));
          } else {
            if (dev->color_depth == 16) 
              drawPixel(dev, x0, y0, ((imgdat[2] >> 3) << 11) | ((imgdat[1] >> 2) << 5) | (imgdat[0] >> 3));
            else {
              drawPixel(dev, x0, y0, (((((int) imgdat[2]) + ((int) imgdat[1]) + ((int) imgdat[0])) > 381) ? 1 : 0));
            }              
          }
          
        } else {
          fseek(fp, img_color_depth, SEEK_CUR);     // Skip image data that isn't on screen
        }        
      }
    } else {
      fseek(fp, img_color_depth * img_width, SEEK_CUR);  // Skip image data that isn't on screen
    }            
  }
  fclose(fp);                                       // Close the file
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

