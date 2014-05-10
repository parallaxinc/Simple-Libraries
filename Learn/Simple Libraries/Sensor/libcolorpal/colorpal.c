/*
 * @file colorpal.c
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


#include "simpletools.h"
#include "colorpal.h"

void colorPal_reset(colorPal *device);
void colorPal_init(colorPal *device);

void colorPal_reset(colorPal *device)
{
  colorPal_t *cp = (colorPal_t*) device->devst;
  low(cp->tx_pin);
  input(cp->rx_pin);
  while(input(cp->rx_pin) == 0);
  low(cp->tx_pin);
  pause(80);
  input(cp->rx_pin);
  pause(10);
}


void colorPal_init(colorPal *device)
{

  colorPal_t *cp = (colorPal_t*) device->devst;

  colorPal_reset(device);
  dprint(device, "=(00 $ m)!");
  pause(10);
  low(cp->rx_pin);
}


void colorPal_getRGB(colorPal *device, int *r, int *g, int *b)
{
  char rs[4], gs[4], bs[4];

  while(readChar(device) != '$');

  memset(rs, 0, 4);
  for(int i = 0; i < 3; i++)
  {
    rs[i] = readChar(device);
  }
  memset(gs, 0, 4);
  for(int i = 0; i < 3; i++)
  {
    gs[i] = readChar(device);
  }
  memset(bs, 0, 4);
  for(int i = 0; i < 3; i++)
  {
    bs[i] = readChar(device);
  }
  sscan(rs, "%x", r);
  sscan(gs, "%x", g);
  sscan(bs, "%x", b);
}


serial *colorPal_open(int sioPin)
{
  int rxpin = sioPin;
  int txpin = rxpin;
  int mode = 0b1100;
  int baudrate = 2400;

  colorPal_t *cpptr;

  text_t* text = (text_t*) malloc(sizeof(text_t));

  // set pins first for boards that can misbehave intentionally like the Quickstart
  if(txpin >= SERIAL_MIN_PIN && txpin <= SERIAL_MAX_PIN) {
    DIRA |=  (1<<txpin);
    OUTA |=  (1<<txpin);
  }
  if(rxpin >= SERIAL_MIN_PIN && rxpin <= SERIAL_MAX_PIN) {
    DIRA &= ~(1<<rxpin);
  }

  //memset(text, 0, sizeof(text_t));
  cpptr = (colorPal_t*) malloc(sizeof(colorPal_t));
  text->devst = cpptr;
  //memset((char*)serptr, 0, sizeof(Serial_t));
  
  text->txChar    = serial_txChar;     /* required for terminal to work */
  text->rxChar    = serial_rxChar;     /* required for terminal to work */

  cpptr->rx_pin  = rxpin; /* recieve pin */
  cpptr->tx_pin  = txpin; /* transmit pin*/
  cpptr->mode    = mode;
  cpptr->baud    = baudrate;
  cpptr->ticks   = CLKFREQ/baudrate; /* baud from clkfreq (cpu clock typically 80000000 for 5M*pll16x) */

  waitcnt(4*CLKFREQ/5+CNT);
  colorPal_init(text);

  return text;
}


void colorPal_close(colorPal *device)
{
  if(!device)
    return;
  colorPal_t *cp = (colorPal_t*) device->devst;
  OUTA &= ~(1 << cp->tx_pin);
  DIRA &= ~(1 << cp->tx_pin);
  DIRA &= ~(1 << cp->rx_pin);
  free((void*)device->devst);
  free(device);
  device = 0;
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

