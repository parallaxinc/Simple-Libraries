/*
 * @file init.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Initializes the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */

//#include <stdlib.h>
#include "simpletools.h"
#include "lis3dh.h"



lis3dh_t *lis3dh_init(int pinSCK, int pinSDI, int pinCS)
{
  
  return lis3dh_init4wire(pinSCK, pinSDI, pinSDI, pinCS); // Initialize in 3-wire SPI mode, with SDI and SDO pins the same
  
} 


lis3dh_t *lis3dh_init4wire(int pinSCK, int pinSDI, int pinSDO, int pinCS)
{
  
  lis3dh_t *device;
  
  
  // allocate memory for device
  if (!(device = (lis3dh_t *)malloc(sizeof(lis3dh_t))))
        return NULL;
  
  // Store IO pins
  device->sdi_pin = pinSDI;
  device->sdo_pin = pinSDO; // Set the same for 3-wire SPI mode
  device->sck_pin = pinSCK;
  device->cs_pin  = pinCS;

  high(device->cs_pin);   // CS high (chip inactive)
   //low(device->sck_pin);  // CLK line low

  // If SPI and SDO are set to the same pin then enable 3-wire SPI mode by setting lowest bit of REG4 to 1
    if (device->sdi_pin == device->sdo_pin) 
       { lis3dh_writeByte(device, LIS3DH_CTRL_REG4, 0b00000001); /* 3-Wire SPI Mode */ } 
  else { lis3dh_writeByte(device, LIS3DH_CTRL_REG4, 0b00000000); /* 4-Wire SPI Mode */ }
  
  pause(5);
  
  lis3dh_setBDUmode(device, LIS3DH_BDUMODE_CONSISTENT);      // Enable BDU (Block Data Update mode) consistent mode - Important! Ensures data updated when both the MSB and LSB bytes are ready.

  lis3dh_writeByte(device, LIS3DH_CTRL_REG1, 0b01110111);    // ODR 400Hz, normal power mode, enable xyz
      
  lis3dh_writeByte(device, LIS3DH_TEMP_CFG_REG, 0b10000000); // Enable ADC
      
      
  // Clear unused configuration registers (in-case they have settings left over from prior experiments)
  lis3dh_writeByte(device, LIS3DH_CTRL_REG2, 0b00000000);
      
  lis3dh_writeByte(device, LIS3DH_CTRL_REG3, 0b00000000);
      
  lis3dh_writeByte(device, LIS3DH_CTRL_REG5, 0b00000000); 
      
  lis3dh_writeByte(device, LIS3DH_CTRL_REG6, 0b00000000);
  
  
  // Set resolution and range
  lis3dh_setResolution(device, 12); // 8, 10 or 12 (bit)
  lis3dh_setRange(device, 2);       // 2, 4, 8 or 16 (g)
  
  pause(100);
  
  
  // Initialise tilt running averages based on current position of sensor
  lis3dh_accel_mg(device, &device->tiltavgX, &device->tiltavgY, &device->tiltavgZ);
  
  // Set tilt moving average filter. Value represents the % of new data, for example 75 would represent 75% of new data, 25% old data    
  device->tiltavg_factor = 100; // default to 100% of new data (ie. filter is off)
       
  
  return device;
  
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





