/*
 * @file abvolts.c
 *
 * @author Andy Lindsay
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2013. All Rights MIT Licensed.
 *
 * @brief Initialize ADC124S021 and measure voltage as a raw, 12-bit5 adc value.
 * @n @n <b><i>CONSTRUCTION ZONE:</i></b> This library is preliminary, revisions 
 * pending.
 * 
 * AD7993* functions contributed by Alex.Stanfield on forums.parallax.com.
 * 
 * Incorporated into a copy of libabvolts by Andy Lindsay. 
 * 
 */

#include "simpletools.h"
#include "boevolts.h"

static int initialized = 0;
#define uint8 unsigned char
i2c *adcBus;                    // I2C bus ID
uint8 adcAddr;                  // Address for this module
uint8 addList[5]= { 0x20, 0x21, 0x22, 0x23, 0x24 }; //I2C bus addresses for ADC
#define AD7993BRUZ_0    (0x21)  // Don't shift addresses, it's done by simpletools
#define AD7993BRUZ_1    (0x23)  // 

int ad7993_init(int address)
{
  uint8 i, t;

  adcBus = i2c_newbus(28,  29,   1);           // Set up I2C bus, get bus ID
  if (address == 0) { //Scan bus for AD7993 chips
    for (i=0; i<sizeof(addList); i++) {
      if (i2c_in(adcBus, addList[i], 0, 0, &t, 1) == 2) {
        adcAddr = addList[i];
        //printf("AD7993 found on 0x%X\n", adcAddr);
        initialized = 1;
        return 1;
      }
    }
  } else {
    if (i2c_in(adcBus, address, 0, 0, &t, 1) == 2) {
      adcAddr = address;
      //printf("AD7993 found on 0x%X\n", adcAddr);
      return 1;
      initialized = 1;
    }
  }
  adcAddr = AD7993BRUZ_0;   //force address if everything else failed
  //printf("AD7993 defaulted to 0x%X\n",adcAddr);
  return 0; //return in error
}


int AD7993in(int channel) {
  uint8 adcVal[2];
  
  if(!initialized)
  {
    ad7993_init(0);
  }    
  
  i2c_out(adcBus, adcAddr, 1<<((channel&3)+4), 1,NULL, 0); //Set channel, mem ptr and start convert
  i2c_in( adcBus, adcAddr, 0, 0, adcVal, 2);               //Get 2 bytes from adc
  
  //return ((adcVal[0] & 0xf) << 6) | (adcVal[1] >> 2);
  return ((adcVal[0] & 0xf) << 6) | (adcVal[1]);
}


int ad_in(int channel)
{
  //AD7993in(channel);
  int val = AD7993in(channel);
  return val;
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
