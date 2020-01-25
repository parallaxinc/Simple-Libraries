/*
 * @file adc_mV.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Reads mV adc measurements from the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



// Helper functions for ADC to mV conversion
// ADC Channel 1 accepts 0-8V (+- 400mV); fromLow is offset to ensure readings at low adc voltages accounting for tolerances
// ADC Channels 2 and 3 accept 900mV to 1800mV (+- 400mV)


// lis3dh_adcMap(valueToMap, fromLow, fromHigh, toLow, toHigh)
int lis3dh_adcMap(int valueToMap, int fromLow, int fromHigh, int toLow, int toHigh) {
    return (valueToMap - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}



void lis3dh_adc_mV(lis3dh_t *device, int *ad1, int *ad2, int *ad3)
{
  int a1, a2, a3;
  
  lis3dh_adc(device, &a1, &a2, &a3);
  
  int res = lis3dh_getResolution(device);
  
  if (res == 8) { // 8-bit samples
    
    *ad1 = lis3dh_adcMap(a1,  69, -128,   0, 8000);
    *ad2 = lis3dh_adcMap(a2, 127, -128, 900, 1800);
    *ad3 = lis3dh_adcMap(a3, 127, -128, 900, 1800); 
  
  } else if (res == 10) { // 10-bit samples

    *ad1 = lis3dh_adcMap(a1, 400, -508,   0, 8000);
    *ad2 = lis3dh_adcMap(a2, 508, -508, 900, 1800);
    *ad3 = lis3dh_adcMap(a3, 508, -508, 900, 1800);    
      
  } else { // 12-bit samples (Note- 10 bit is maximum ADC resolution, but data presented as 12-bit if XYZ sampling is 12-bit)

    *ad1 = lis3dh_adcMap(a1, 1600, -2032,   0, 8000);
    *ad2 = lis3dh_adcMap(a2, 2032, -2032, 900, 1800);
    *ad3 = lis3dh_adcMap(a3, 2032, -2032, 900, 1800);    
      
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




