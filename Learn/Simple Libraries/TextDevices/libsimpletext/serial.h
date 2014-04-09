/**
 * @file SimpleSerial.h
 * Defines serial module
 *
 * Copyright (c) 2013, Parallax Inc.
 * Written by Steve Denson
 * Symbol naming decided by Parallax
 */
#ifndef __SERIAL_H
#define __SERIAL_H

#include "simpletext.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** 
 * @brief Min serial pin value.
 */ 
#define SERIAL_MIN_PIN 0

/** 
 * @brief Max serial pin value.
 */ 
#define SERIAL_MAX_PIN 31

typedef struct serial_info
{
  int rx_pin;
  int tx_pin;
  int mode;
  int baud;
  int ticks;
} Serial_t;

/**
 * @brief Makes declarations like serial lcd to stand in for text_t lcd.
 * Spelling is choice of Parallax education, not the author.
 */
typedef text_t serial;

/**
 * @brief Open a simple serial connection.  
 *
 * @param rxpin Serial input pin, receives serial data.
 * 
 * @param txpin Serial output pin, transmits serial data.
 * 
 * @param mode Unused mode field (for FdSerial compatibility)
 * 
 * @param baudrate Bit value transmit rate, 9600, 115200, etc...
 *
 * @returns device ID pointer for use with simpletext.h and serial.h functions
 * with text_t or serial.
 */
serial *serial_open(int rxpin, int txpin, int mode, int baudrate);


/**
 * @brief Close serial connection.  
 * 
 * @param device A previously opened serial connection.
 */
void serial_close(serial *device);

                         
/**
 * @brief Receive a byte.  Waits until next byte is recieved.
 *
 * @param device ID returned by serial_open.
 *
 * @returns receive byte 0 to 0xff or -1 if none available 
 */
int  serial_rxChar(serial *device);


/**
 * @brief Send a byte.
 * 
 * @param device is a previously open/started terminal device.
 * 
 * @param device ID returned by serial_open.
 * 
 * @returns Byte that was transmitted. 
 */
int  serial_txChar(serial *device, int txbyte);

#ifdef __cplusplus
}
#endif

#endif
/* __SERIAL_H */

/*
+--------------------------------------------------------------------
| TERMS OF USE: MIT License
+--------------------------------------------------------------------
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+--------------------------------------------------------------------
*/
