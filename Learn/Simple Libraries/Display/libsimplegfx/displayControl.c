/*
 * @file displayControl.c
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


void clearDisplay(screen_t *dev) {
  dev->deviceClearDisplay(dev);
}
  
void updateDisplay(screen_t *dev) {
  dev->deviceUpdateDisplay(dev);
}
  
void resetDisplay(screen_t *dev) {
  dev->deviceResetDisplay(dev);
}

void setDisplayRotation(screen_t *dev, char r) {
  dev->rotation = r;
}

char getDisplayRotation(screen_t *dev) {
  return dev->rotation;
}

int getDisplayWidth(screen_t *dev) {
  if (dev->rotation & 1) {
    return dev->height;
  } else {
    return dev->width; 
  }        
}

int getDisplayHeight(screen_t *dev) {
  if (dev->rotation & 1) {
    return dev->width;
  } else {
    return dev->height; 
  }        
}

void drawCopy(screen_t *dev, int x, int y, int w, int h, int x1, int y1) {
  dev->deviceCopyRect(dev, x, y, w, h, x1, y1);
}

void invertDisplay(screen_t *dev, char i) {                           
  dev->deviceInvertDisplay(dev, i);
  if (i) dev->display_mode |=  (i & 0b01);
  else   dev->display_mode &= ~(i & 0b01);
}

void sleepWakeDisplay(screen_t *dev, char i) {
  dev->deviceSleepWakeDisplay(dev, i);
  if (i) dev->display_mode |=  (i & 0b10);
  else   dev->display_mode &= ~(i & 0b10);
}

void scrollDisplay(screen_t *dev, int  h, int v) {
  dev->deviceScrollDisplay(dev, h, v);
  dev->display_mode &= ~0xffff00;
  dev->display_mode |=  ((v & 0xff) << 16);
  dev->display_mode |=  ((h & 0xff) << 16);
}

char isInverted(screen_t *dev) {
  return (dev->display_mode & 0b01);
}

char isAsleep(screen_t *dev) {
  return ((dev->display_mode & 0b10) >> 1);
}

unsigned char getScrollHorizontal(screen_t *dev) {
  return (unsigned char) ((dev->display_mode >> 16) & 0xff);
}

unsigned char getScrollVertical(screen_t *dev) {
  return (unsigned char) ((dev->display_mode >> 8) & 0xff);
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
