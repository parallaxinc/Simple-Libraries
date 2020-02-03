
/*
 * @file tilt.c
 *
 * @author Michael Mulholland
 *
 * @version 1.0.0
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2019. All Rights MIT Licensed.
 *
 * @brief Gets tilt angle measurements for all axis for the Parallax LIS3DH 3-Axis Accelerometer Module with ADC.
 * 
 * @detail Resolution is user-configured in the sensor as 8, 10 or 12 bit. (Refer to setResolution and getResolution functions)
 *         Recommended to use 2g acceleration range (setRange) for tilt sensing
 * 
 * @returns 1 if data available and angles for all 3 axis (x, y, z). Otherwise returns 0.
 * 
 */


#include "simpletools.h"
#include "lis3dh.h"



// Helper function for Tilt angle value limiting

int lis3dh_limitangle(int angle) {
  
  if (angle < -90) { return -90; }
  if (angle >  90) { return  90; }
  return angle;
  
}

// Helper function to apply scale and rounding to tilt angles

int lis3dh_scaleresult(int value) {
  
  int i, r;
  
  i = value / 100;
  r = value - (i * 100);
  
  return (r > 49) ? ++i : i;
    
}

  
int lis3dh_tilt(lis3dh_t *device, int *ax, int *ay, int *az, int *motion)
{
        
  int x, y, z;
  int avg_factor = device->tiltavg_factor;
    
  if (lis3dh_accel_mg(device, &x, &y, &z)) {
    
    // Calculate moving average (low pass filter)
    // Setting the avg_factor value to 0 or 100 will disable the filter.
    
    if ((avg_factor > 0) && (avg_factor < 100)) {
      
        x = lis3dh_scaleresult((x * avg_factor) + (device->tiltavgX * (100 - avg_factor )));
        y = lis3dh_scaleresult((y * avg_factor) + (device->tiltavgY * (100 - avg_factor )));
        z = lis3dh_scaleresult((z * avg_factor) + (device->tiltavgZ * (100 - avg_factor )));
        
        device->tiltavgX = x; // Write back averages for next time
        device->tiltavgY = y;
        device->tiltavgZ = z;
    
    }   
    

    // Calculate angle to each axis in radians
    
    // X relative to ground
    // Y relative to ground
    // Z relative to gravity
    
    float y_radians = atan(((float)y/(sqrt(x*x + z*z))));
    float x_radians = atan(((float)x/(sqrt(y*y + z*z))));
    float z_radians = atan((sqrt(x*x + y*y) / z));
    
    // Convert angles from radians to degrees
    // 1 radian × 180/pi = 57.296°

    *ay = lis3dh_limitangle( (int) (y_radians * 57.3) );
    *ax = lis3dh_limitangle( (int) (x_radians * 57.3) );
    *az = lis3dh_limitangle( (int) (z_radians * 57.3) );
    
    // Calculate motion value; 0 at 1G, increases or decreases with motion detected (sign represents dominant direction)
    *motion = (int) (sqrt(x*x + y*y + z*z)) - 1000; // Deduct 1G (1000 milliG's) from result to offset from ground level.
  
  
    return 1; // OK !
    
  }
  
  return 0; // Return 0 if no data available                                       
  
}



int lis3dh_tiltConfig(lis3dh_t *device, int avg_factor) {
                        
  if ((avg_factor < 0) || (avg_factor > 100)) 
  { 
    return 0; // Invalid ratio
  }
  
  
  device->tiltavg_factor = avg_factor;
  return 1;  // Configuration values accepted OK
    
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



