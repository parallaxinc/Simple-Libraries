/**
 * @file colorpal.h
 *
 * @author Andy Lindsay
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2012. All Rights MIT Licensed.
 *
 * @brief Simplifies reading Parallax ColorPAL sensor.
 */


#ifndef COLORPAL_H
#define COLORPAL_H

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * Defines instance of colorpal_t settings for serial communication.
 */
typedef struct colorpal_serinfo
{
  int rx_pin;
  int tx_pin;
  int mode;
  int baud;
  int ticks;
} colorPal_t;


/**
 * Defines instance of colorpal for use with simpletext functions that 
 * accept text_t parameters.
 */
typedef text_t colorPal;


/**
 * @brief Open a connection to a Parallax ColorPAL sensor.
 *
 * @param sioPin Propeller I/O pin connected to ColorPAL sensor's
 * SIO pin.
 *
 * @returns colorPal device identifier for use with functions in colorpal library and 
 * functions with text_t parameter in simpletext library. 
 */
colorPal *colorPal_open(int sioPin);


/**
 * @brief Close a connection and recover all memory set aside for the ColorPal 
 * sensor instance.
 *
 * @param *device device identifier returned by colorPal_open function.
 */
void colorPal_close(colorPal *device);


/**
 * @brief Get RGB (red green blue) values from the ColorPAL sensor.
 *
 * @param *device device identifier returned by colorPal_open function.
 *
 * @param r Red value.
 *
 * @param g Green value.
 *
 * @param b Blue value.
 */
void colorPal_getRGB(colorPal *device, int *r, int *g, int *b);


#if defined(__cplusplus)
}
#endif
/* __cplusplus */ 
#endif
/* COLORPAL_H */ 


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



