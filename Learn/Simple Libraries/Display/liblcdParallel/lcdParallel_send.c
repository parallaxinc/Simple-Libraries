/**
 * @file lcdParallel_send.c
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


#include "lcdParallel.h"
#include "simpletools.h"

void lcdParallel_writeChar(lcdParallel *device, char value) {
  lcdParallel_send(device, value, LCDP_SEND_WRITE);
}  

// write either command or data, with automatic 4/8-bit selection
void lcdParallel_send(lcdParallel *device, char value, char mode) {
  set_output(device->_rs_pin, mode);

  
  if (device->_displayfunction & LCDP_8BITMODE) {
    lcdParallel_write(device, value, 8); 
  } else {
    lcdParallel_write(device, value >> 4, 4);
    lcdParallel_write(device, value, 4);
  }
}

void lcdParallel_write(lcdParallel *device, char value, char bits) {
  set_outputs(device->_data_pins[bits - 1], device->_data_pins[0], (value & (bits == 4 ? 15 : 255)));
  low(device->_enable_pin);
  usleep(1);    
  high(device->_enable_pin);
  usleep(1);     // enable pulse must be > 0.5us
  low(device->_enable_pin);
  usleep(100);   // commands need > 40us to settle
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
