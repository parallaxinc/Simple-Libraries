/*
 * @file accel_mg.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Read acceleration (G-Force) for the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 * @returns 1 if data available and acceleration for all 3 axis in milli-g's (xmg ymg zmg). Otherwise returns 0.
 * 
 */

/*
 * From datasheet, 1 LSb = X mg, where X is shown in this table, depending on active Range and Resolution:
 *
 * Range  8-bit   10-bit  12-bit
 * ±2g    16      4       1
 * ±4g    32      8       2
 * ±8g    64      16      4
 * ±16g   192     48      12 
*/


#include "simpletools.h"
#include "lis3dh.h"



int lis3dh_accel_mg(lis3dh_t *device, int *xmg, int *ymg, int *zmg) {
  
  int x, y, z;
  
  if (lis3dh_accel(device, &x, &y, &z)) { // Get acceleration values from sensor

    unsigned char res = lis3dh_getResolution(device);
    unsigned char range = lis3dh_getRange(device);
    unsigned char mgLSB = range * 8;
    
        if (range == 16) { mgLSB += 64; }
  
	      if (res == 10) { mgLSB = mgLSB >> 2; }
  
	 else if (res == 12) { mgLSB = mgLSB >> 4; }
 
	 *xmg = x * mgLSB;
	 *ymg = y * mgLSB;
	 *zmg = z * mgLSB;
  
    return 1;
  
  } else { 
  
    return 0; 
    
  }
  
}


int lis3dh_getAccel_mg(lis3dh_t *device, int axis)
{
  
  int x, y, z;
  
  if (lis3dh_accel_mg(device, &x, &y, &z)) {
  
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