/*
 * @file adc.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Reads adc measurements from the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



void lis3dh_adc(lis3dh_t *device, int *ad1, int *ad2, int *ad3)
{
    
  int res = 16 - lis3dh_getResolution(device);
      
  low(device->cs_pin);
  
  shift_out(device->sdi_pin, device->sck_pin, MSBFIRST, 8, LIS3DH_OUT_ADC1_L | LIS3DH_MASK_READREPEAT); // Read mask with automatic address advance
  
  signed short s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
  s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
  *ad1 = ((int)s) >> res;
  
  s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
  s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
  *ad2 = ((int)s) >> res;
  
  s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
  s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
  *ad3 = ((int)s) >> res;

  high(device->cs_pin);
                                 
  
}


int lis3dh_getADC(lis3dh_t *device, int channel)
{
  
  int ad1, ad2, ad3;
  
  lis3dh_adc(device, &ad1, &ad2, &ad3);
  
  switch (channel) {
    
      case  1 : return ad1; 
      case  2 : return ad2;
      case  3 : return ad3;
      default : return 0;
  
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



