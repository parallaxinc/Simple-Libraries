/*
 * @file drawLine.c
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


// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (0, 0) and (w, h)

int ComputeOutCode(int x, int y, int w, int h) {
  int code = 0b0000;                    // initialised as being inside of clip window

  if      (x < 0)   code |= 0b0001;     // to the left of clip window
  else if (x >= w)  code |= 0b0010;     // to the right of clip window
  if      (y < 0)   code |= 0b1000;     // below the clip window
  else if (y >= h)  code |= 0b0100;     // above the clip window

  return code;
}

void drawLine(screen_t *dev, int x0, int y0, int x1, int y1, int c) {
  // check rotation, move pixel around if necessary
  switch (dev->rotation) {
    case 1:
      gfx_swap(x0, y0);
      gfx_swap(x1, y1);
      x0 = dev->width - x0 - 1;
      x1 = dev->width - x1 - 1;
      //gfx_swap(x0, x1);
      break;
    case 2:
      gfx_swap(x0, x1);
      gfx_swap(y0, y1);
      x0 = dev->width - x0 - 1;
      y0 = dev->height - y0 - 1;
      x1 = dev->width - x1 - 1;
      y1 = dev->height - y1 - 1;
      break;
    case 3:
      gfx_swap(x0, y0);
      gfx_swap(x1, y1);
      y0 = dev->height - y0 - 1;
      y1 = dev->height - y1 - 1;
      //gfx_swap(y0, y1);
      break;
  }

  // Cohen–Sutherland clipping algorithm clips a line from
  // P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
  // diagonal from (xmin, ymin) to (xmax, ymax).
  // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle

  int outcode0 = ComputeOutCode(x0, y0, dev->width, dev->height);
  int outcode1 = ComputeOutCode(x1, y1, dev->width, dev->height);
  char accept = 0;

  while (1) {
    if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
      accept = 1;
      break;
    } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
      break;
    } else {
      // failed both tests, so calculate the line segment to clip
      // from an outside point to an intersection with clip edge
      int x, y;

      // At least one endpoint is outside the clip rectangle; pick it.
      int outcodeOut = outcode0 ? outcode0 : outcode1;

      // Now find the intersection point;
      // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
      if (outcodeOut & 0b1000) { // point is above the clip rectangle
        x = x0 + (x1 - x0) * (0 - y0) / (y1 - y0);
        y = 0;
      } else if (outcodeOut & 0b0100) {           // point is below the clip rectangle
        x = x0 + (x1 - x0) * (dev->height - y0 - 1) / (y1 - y0);
        y = dev->height - 1;
      } else if (outcodeOut & 0b0010) {  // point is to the 0b0010 of clip rectangle
        y = y0 + (y1 - y0) * (dev->width - x0 - 1) / (x1 - x0);
        x = dev->width - 1;
      } else if (outcodeOut & 0b0001) {   // point is to the 0b0001 of clip rectangle
        y = y0 + (y1 - y0) * (0 - x0) / (x1 - x0);
        x = 0;
      }

      // Now we move outside point to intersection point to clip
      // and get ready for next pass.
      if (outcodeOut == outcode0) {
        x0 = x;
        y0 = y;
        outcode0 = ComputeOutCode(x0, y0, dev->width, dev->height);
      } else {
        x1 = x;
        y1 = y;
        outcode1 = ComputeOutCode(x1, y1, dev->width, dev->height);
      }
    }
  }
  
  if (accept && !dev->deviceDrawLine) {
    int dx = x1 - x0;
    signed char ix = (dx > 0) - (dx < 0);
    dx = absv(dx) << 1;
  
    int dy = y1 - y0;
    signed char iy = (dy > 0) - (dy < 0);
    dy = absv(dy) << 1;
  
    dev->deviceDrawPixel(dev, x0, y0, c);
  
    if( dx >= dy ) {
      int err = dy - (dx >> 1);
      while(x0 != x1) {
        if( (err >= 0) && (err || (ix > 0)) ) {
          err -= dx;
          y0 += iy;
        }
        err += dy;
        x0 += ix;
        
        dev->deviceDrawPixel(dev, x0, y0, c);
      }
    } else {
      int err = dx - (dy >> 1);
      while(y0 != y1) {
        if( (err >= 0) && (err || (iy > 0)) ) {
          err -= dy;
          x0 += ix;
        }
        err += dx;
        y0 += iy;
        
        dev->deviceDrawPixel(dev, x0, y0, c);
      }
    }    
  } else if (accept) {
    dev->deviceDrawLine(dev, x0, y0, x1, y1, c);
  }   
}

void drawFastHLine(screen_t *dev, int x, int y, int w, int color) {
  if((y >= 0) && (y < getDisplayHeight(dev))) { // Y coord in bounds?
    if(x < 0) { // Clip left
      w += x;
      x  = 0;
    }
    if((x + w) > getDisplayWidth(dev)) { // Clip right
      w = (getDisplayWidth(dev) - x);
    }

    char bSwap = 0;
    switch(dev->rotation) {
     case 1:   // 90 degree rotation, swap x & y for rotation, then invert x
      bSwap = 1;
      gfx_swap(x, y);
      x = dev->width - x - 1;
      break;
     case 2:   // 180 degree rotation, invert x and y, then shift y around for height.
      x  = dev->width  - x - 1;
      y  = dev->height - y - 1;
      x -= (w - 1);
      break;
     case 3:   // 270 degree rotation, swap x & y then invert y and adjust y for w.
      bSwap = 1;
      gfx_swap(x, y);
      y  = dev->height - y - 1;
      y -= (w - 1);
      break;
    }
       
    if(bSwap) dev->deviceDrawFastVLine(dev, x, y, w, color);
    else      dev->deviceDrawFastHLine(dev, x, y, w, color);
  }
}

void drawFastVLine(screen_t *dev, int x, int y, int h, int color) {

  if((x >= 0) && (x < getDisplayWidth(dev))) { // Y coord in bounds?
    char bSwap = 0;

    if(y < 0) { // Clip top
      h += y;
      y  = 0;
    }
    if((y + h) > getDisplayHeight(dev)) { // Clip bottom
      h = (getDisplayHeight(dev) - y);
    }
    
    switch(dev->rotation) {
     case 1:
      // 90 degree rotation, swap x & y for rotation,
      // then invert x and adjust x for h (now to become w)
      bSwap = 1;
      gfx_swap(x, y);
      x  = dev->width - x - 1;
      x -= (h-1);
      break;
     case 2:
      // 180 degree rotation, invert x and y, then shift y around for height.
      x = dev->width  - x - 1;
      y = dev->height - y - 1;
      y -= (h-1);
      break;
     case 3:
      // 270 degree rotation, swap x & y for rotation, then invert y
      bSwap = 1;
      gfx_swap(x, y);
      y = dev->height - y - 1;
      break;
    }

    if(bSwap) dev->deviceDrawFastHLine(dev, x, y, h, color);
    else      dev->deviceDrawFastVLine(dev, x, y, h, color);
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
