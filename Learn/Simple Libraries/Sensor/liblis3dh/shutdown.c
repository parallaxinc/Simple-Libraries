/*
 * @file shutdown.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Clears registers, buffers and disables the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



void lis3dh_shutdown(lis3dh_t *device)
{
  
  high(device->cs_pin);   // CS high (chip inactive)
  //low(device->sck_pin);   // CLK line low

    // If SPI and SDO are set to the same pin then enable 3-wire SPI mode by setting lowest bit of REG4 to 1
    if (device->sdi_pin == device->sdo_pin) 
       { lis3dh_writeByte(device, LIS3DH_CTRL_REG4, 0b00000001); /* 3-Wire SPI Mode */ } 
  else { lis3dh_writeByte(device, LIS3DH_CTRL_REG4, 0b00000000); /* 4-Wire SPI Mode */ }

  pause(5);
  
  // Clear all configuration registers back to defaults, except REG4 which holds the SPI-mode
  
  lis3dh_writeByte(device, LIS3DH_CTRL_REG2, 0b00000000); //
  lis3dh_writeByte(device, LIS3DH_CTRL_REG3, 0b00000000); //
  lis3dh_writeByte(device, LIS3DH_CTRL_REG5, 0b10000000); // Reboot (clear) memory buffer contents 
  lis3dh_writeByte(device, LIS3DH_CTRL_REG6, 0b00000000); //
  lis3dh_writeByte(device, LIS3DH_TEMP_CFG_REG, 0b00000000); // 
  
  lis3dh_writeByte(device, LIS3DH_CTRL_REG1, 0b00000000); // Disable sensor
  
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

