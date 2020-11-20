/*
 * @file adc_mV.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.1
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2020. All Rights MIT Licensed.
 *
 * @brief Reads mV adc measurements from the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



// Helper functions for ADC to mV conversion
// ADC Channel 1 accepts 0-7800mV (+- 200mV); fromLow is offset to ensure readings at low adc voltages accounting for tolerances
// ADC Channels 2 and 3 accept 900mV to 1700mV (+- 100mV)


// lis3dh_adcMap(valueToMap, fromLow, fromHigh, toLow, toHigh)
int lis3dh_adcMap(int valueToMap, int fromLow, int fromHigh, int toLow, int toHigh) {
    
    return ((valueToMap - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow);

}



void lis3dh_adc_mV(lis3dh_t *device, int *ad1, int *ad2, int *ad3)
{
  int a1, a2, a3;
  
  lis3dh_adc(device, &a1, &a2, &a3);
  
  int res = lis3dh_getResolution(device);
  
  
  if (res == 8) { // 8-bit samples, -128 to 127
    
    *ad1 = lis3dh_adcMap(a1,  87, -128,   0, 7800);
    *ad2 = lis3dh_adcMap(a2, 127, -128, 900, 1700);
    *ad3 = lis3dh_adcMap(a3, 127, -128, 900, 1700); 
  
  } else if (res == 10) { // 10-bit samples, -512 to 511

    *ad1 = lis3dh_adcMap(a1, 350, -508,   0, 7800);
    *ad2 = lis3dh_adcMap(a2, 508, -508, 900, 1700);
    *ad3 = lis3dh_adcMap(a3, 508, -508, 900, 1700);   
      
  } else { // 12-bit samples, -2048 to 2047
           // (Note- 10 bit is maximum ADC resolution, but data presented as 12-bit if XYZ sampling is 12-bit)

    *ad1 = lis3dh_adcMap(a1, 1400, -2032,   0, 7800); // Offset the minimum value as lowest AD1 voltage about 0.97V (post divider)
    *ad2 = lis3dh_adcMap(a2, 2032, -2032, 900, 1700);
    *ad3 = lis3dh_adcMap(a3, 2032, -2032, 900, 1700);   
      
  } 
  
  
  // Calibration of AD1
    
  if ((device->adccal_m1000 != 0) || (device->adccal_b1000 != 0)) {
  
    *ad1 = ((*ad1 * device->adccal_m1000) + device->adccal_b1000) / 1000;
          
  }
 
          
}


int lis3dh_getADC_mV(lis3dh_t *device, int channel)
{
  
  int ad1, ad2, ad3;
  
  lis3dh_adc_mV(device, &ad1, &ad2, &ad3);
  
  switch (channel) {
    
      case  1 : return ad1; 
      case  2 : return ad2;
      case  3 : return ad3;
      default : return 0;
  
    }

}


void lis3dh_adcCal_mV(lis3dh_t *device, int mV_L, int mV_H, int value_L, int value_H) 
{
  
  if (mV_L == 0 & mV_H == 0 & value_L == 0 & value_H == 0) {
  
    device->adccal_m1000 = 0;
    device->adccal_b1000 = 0;
      
  } else {
        
    device->adccal_m1000 = (1000 * mV_H) / (value_H + (value_L * -1));
    device->adccal_b1000 = (device->adccal_m1000 * value_L) * -1;
  
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




