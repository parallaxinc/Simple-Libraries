/*
 * @file setBDUmode.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Sets BDU (Block Data Update) mode for the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



void lis3dh_setBDUmode(lis3dh_t *device, int mode)
{
  
  unsigned char reg = lis3dh_readByte(device, LIS3DH_CTRL_REG4);
  
  // Set or clear BDU bit, according to required mode
  reg = (mode == LIS3DH_BDUMODE_CONSISTENT) ? reg | LIS3DH_MASK_BDUMODE : reg & ~LIS3DH_MASK_BDUMODE;
  
  
  lis3dh_writeByte(device, LIS3DH_CTRL_REG4, reg);

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


