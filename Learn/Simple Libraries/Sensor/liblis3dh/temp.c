/*
 * @file temp.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Read and calibrate temperature for the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



// Temperature sensor output change vs temperature: 8-bit resolution, 1 digit / degrees Celsius

int lis3dh_tempRaw(lis3dh_t *device) {
  
  
  unsigned char r = lis3dh_readByte(device, LIS3DH_TEMP_CFG_REG);   // Capture register configuration
  
  lis3dh_writeByte(device, LIS3DH_TEMP_CFG_REG, 0b11000000);        // Ensure ADC and Temp sensor enabled
  
  pause(20);
  
  int t = lis3dh_getADC(device, 3);
  t = 0;                                                            // Ignore first reading
  
  for (int i=0; i<=5; i++)
  {
    pause(20);                                                      // Minimum of an ODR pause between readings
    t += lis3dh_getADC(device, 3) >> 2;                             // Read raw temp value
  }
  
  lis3dh_writeByte(device, LIS3DH_TEMP_CFG_REG, r);                 // Revert register configuration to initial state
  
  return t / 5;                                                     // return average of the readings   
  
}
  
  
int lis3dh_temp_C(lis3dh_t *device)
{
  
  // tempRaw and tempcalC both in Celcius; no conversions required before calculating absolute temperature
  return lis3dh_tempRaw(device) + device->tempcalC;
  
}


int lis3dh_temp_F(lis3dh_t *device)
{
  
  // convert lis3dh_temp_C to Fahrenheit
  return (((lis3dh_temp_C(device) * 9) / 5) + 32);                  // °C to °F Multiply by 9, then divide by 5, then add 32
  
}


void lis3dh_tempCal_C(lis3dh_t *device, int actualTemp) 
{
  
  // tempRaw and actualTemp both in Celcius; no conversions required
  device->tempcalC = actualTemp - lis3dh_tempRaw(device);
  
    
}  


void lis3dh_tempCal_F(lis3dh_t *device, int actualTemp) 
{
  
  // tempRaw always in Celcius, so convert actualTemp from Fahrenheit to Celcius before storing the calibration value
    
  int f = (((actualTemp - 32) * 5) / 9);                            // °F to °C	 Deduct 32, then multiply by 5, then divide by 9
  if (((actualTemp * 18) % 10) > 5) { f++; }                        // Round-up
                               
  lis3dh_tempCal_C(device, f);
  
}  
  
/*int lis3dh_getTempCal_C(lis3dh_t *device) {
  
  return device->tempcalC;
 
}*/  



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



