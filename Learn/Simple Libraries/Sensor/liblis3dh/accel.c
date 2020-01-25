/*
 * @file accel.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Gets raw axis measurements for the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 * @detail Resolution is user-configured in the sensor as 8, 10 or 12 bit. (Refer to setResolution and getResolution functions)
 * 
 * @returns 1 if data available and raw acceleration values for all 3 axis (x, y, z). Otherwise returns 0.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



int lis3dh_accel(lis3dh_t *device, int *x, int *y, int *z)
{
  
      
  if ((lis3dh_readByte(device, LIS3DH_STATUS_REG) & 0x08) == 8) { // XYZ Data Available
    
    int res = 16 - lis3dh_getResolution(device);
        
    low(device->cs_pin);
    
    shift_out(device->sdi_pin, device->sck_pin, MSBFIRST, 8, LIS3DH_OUT_X_L | LIS3DH_MASK_READREPEAT); // Read mask with automatic address advance
    
    signed short s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
    s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
    *x = ((int)s) >> res;
    
    s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
    s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
    *y = ((int)s) >> res;
    
    s = shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
    s |= (unsigned short)(shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8) << 8);
    *z = ((int)s) >> res;
  
    high(device->cs_pin);
    
    return 1;
    
  } else {
    
    return 0; // No data available
    
  }                                       
  
}


int lis3dh_getAccel(lis3dh_t *device, int axis)
{
  
  int x, y, z;
  
  if (lis3dh_accel(device, &x, &y, &z)) {
  
    switch (axis) {
    
      case  1 : return x; 
      case  2 : return y;
      case  3 : return z;
        
    }
  }
  
  return 0; // Return 0 if no data available, or invalid axis requested
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



