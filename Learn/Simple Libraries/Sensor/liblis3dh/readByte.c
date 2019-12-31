/*
 * @file readByte.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Reads a byte from a register in the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"                        
#include "lis3dh.h"



unsigned char lis3dh_readByte(lis3dh_t *device, unsigned char address)
{
  
  low(device->cs_pin);                                   
    
  shift_out(device->sdi_pin, device->sck_pin, MSBFIRST, 8, address | LIS3DH_MASK_READSINGLE); // Mask address for single address read
  
  unsigned char reply = (unsigned char)shift_in(device->sdo_pin, device->sck_pin, MSBPRE, 8);
  
  high(device->cs_pin);
                                    
  return reply;
  
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



