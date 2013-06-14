/**
 * @file SimpleSerial.c
 * Defines the SimpleSerial module
 *
 * Copyright (c) 2013, Parallax Inc.
 * Written by Steve Denson
 */
#include <stdlib.h>
#include <propeller.h>
#include "serial.h"

serial *serial_open(int rxpin, int txpin, int mode, int baudrate)
{
  Serial_t *serptr;

  /* can't use array instead of malloc because it would go out of scope. */
  text_t* text = (text_t*) malloc(sizeof(text_t));

  /* set pins first for boards that can misbehave intentionally like the Quickstart */
  DIRA |=  (1<<txpin);
  OUTA |=  (1<<txpin);
  DIRA &= ~(1<<rxpin);

  //memset(text, 0, sizeof(text_t));
  serptr = (Serial_t*) malloc(sizeof(Serial_t));
  text->devst = serptr;
  //memset((char*)serptr, 0, sizeof(Serial_t));
  
  text->txChar    = serial_txChar;     /* required for terminal to work */
  text->rxChar    = serial_rxChar;     /* required for terminal to work */

  serptr->rx_pin  = rxpin; /* recieve pin */
  serptr->tx_pin  = txpin; /* transmit pin*/
  serptr->mode    = mode;
  serptr->baud    = baudrate;
  serptr->ticks   = CLKFREQ/baudrate; /* baud from clkfreq (cpu clock typically 80000000 for 5M*pll16x) */

  waitcnt(CLKFREQ/2+CNT);
  return text;
}

__attribute__((fcache)) static int _inbyte(int bitcycles, int cycle1, int rxmask, int value)
{
  int waitcycles;
  int j = 8;

  /* wait for a start bit */
  waitpeq(0, rxmask);
  waitcycles = cycle1 + CNT;

  /* index initialized above */
  while(j-- > 0) {
    /* C code is too big for fcache in xmm memory models.
    // waitcycles = waitcnt2(waitcycles, bitcycles); */
    __asm__ volatile("waitcnt %[_waitcycles], %[_bitcycles]"
                     : [_waitcycles] "+r" (waitcycles)
                     : [_bitcycles] "r" (bitcycles));

    /* value = ( (0 != (INA & rxmask)) << 7) | (value >> 1); */
    __asm__ volatile("shr %[_value],# 1\n\t"
                     "test %[_mask],ina wz \n\t"
                     "muxnz %[_value], #1<<7"
                     : [_value] "+r" (value)
                     : [_mask] "r" (rxmask));
  }
  return value; /* fcached 0x40 or 64 bytes */
}

int  serial_rxChar(serial *device)
{
  Serial_t *sp = (Serial_t*) device->devst;
  int value = 0;

  /* set input */
  unsigned int rxmask = 1 << sp->rx_pin;
  DIRA &= ~rxmask;

  value = _inbyte(sp->ticks, sp->ticks + (sp->ticks>>20), rxmask, 0);
  /* wait for the line to go high (as it will when the stop bit arrives) */
  waitpeq(rxmask, rxmask);
  return value & 0xff;
}

__attribute__((fcache)) static void _outbyte(int bitcycles, int txmask, int value)
{
  int j = 10;
  int waitcycles;

  waitcycles = CNT + bitcycles;
  while(j-- > 0) {
    /* C code is too big and not fast enough for all memory models.
    // waitcycles = waitcnt2(waitcycles, bitcycles); */
    __asm__ volatile("waitcnt %[_waitcycles], %[_bitcycles]"
                     : [_waitcycles] "+r" (waitcycles)
                     : [_bitcycles] "r" (bitcycles));

    /* if (value & 1) OUTA |= txmask else OUTA &= ~txmask; value = value >> 1; */
    __asm__ volatile("shr %[_value],#1 wc \n\t"
                     "muxc outa, %[_mask]"
                     : [_value] "+r" (value)
                     : [_mask] "r" (txmask));
  }
}


int serial_txChar(serial *device, int value)
{
  Serial_t *sp = (Serial_t*) device->devst;
  int txmask = (1 << sp->tx_pin);
  DIRA |= txmask;

  _outbyte(sp->ticks, txmask, (value | 0x100) << 1);

  return value;
}

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

