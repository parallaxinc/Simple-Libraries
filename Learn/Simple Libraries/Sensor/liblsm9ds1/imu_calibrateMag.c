/**
 * @file LSM9DS1_calibrateMag.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2016. All Rights MIT Licensed.
 *
 * @brief This Propeller C library was created for the Parallax 9-axis IMU Sensor, based
 * on the STMicroelectronics LSM9DS1 inertial motion sensor chip.
 */



#include "lsm9ds1.h"


void imu_calibrateMag()
{

  int i = 0, j, mx, my, mz;
  int magMin[3] = {0, 0, 0};
  int magMax[3] = {0, 0, 0};
  
  while(i < 1200)  // ~40 samples/second = ~30 seconds
  {

    while (!imu_magAvailable(ALL_AXIS));
    imu_readMag(&mx, &my, &mz);
    int magTemp[3] = {0, 0, 0};
    magTemp[0] = mx;
    magTemp[1] = my;
    magTemp[2] = mz;
    
    for (j = 0; j < 3; j++)
    {
      if (magTemp[j] > magMax[j]) magMax[j] = magTemp[j];   // finds the smallest and largest values
      if (magTemp[j] < magMin[j]) magMin[j] = magTemp[j];
    }
    
    i++;
  }

  mx = (magMax[0] + magMin[0]) / 2;   // sets the Bias as the average of the high and low values
  my = (magMax[1] + magMin[1]) / 2;
  mz = (magMax[2] + magMin[2]) / 2;
  
  imu_setMagCalibration(mx, my, mz);
}



/*
 * Based on the Arduino Library for the LSM9SD1 by Jim Lindblom of Sparkfun Electronics
 */

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