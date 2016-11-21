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


int __pinM;
//float __mRes;
int __mBiasRaw[3] = {0,0,0};


void imu_calibrateMag()
{
  int i, j, mx, my, mz;
  int magMin[3] = {0, 0, 0};
  int magMax[3] = {0, 0, 0}; // The road warrior
  
  for (i=0; i<128; i++)
  {
    while (!imu_magAvailable(ALL_AXIS));
    imu_readMag(&mx, &my, &mz);
    int magTemp[3] = {0, 0, 0};
    magTemp[0] = mx;    
    magTemp[1] = my;
    magTemp[2] = mz;
    for (j = 0; j < 3; j++)
    {
      if (magTemp[j] > magMax[j]) magMax[j] = magTemp[j];
      if (magTemp[j] < magMin[j]) magMin[j] = magTemp[j];
    }
  }

  for (j = 0; j < 3; j++)
  {
    __mBiasRaw[j] = (magMax[j] + magMin[j]) / 2;
  }
  
  unsigned char msb, lsb;
  for(int k = 0; k < 3; k++)
  {
    msb = (__mBiasRaw[k] & 0xFF00) >> 8;
    lsb = __mBiasRaw[k] & 0x00FF;
    imu_SPIwriteByte(__pinM, OFFSET_X_REG_L_M + (2 * k), lsb);
    imu_SPIwriteByte(__pinM, OFFSET_X_REG_H_M + (2 * k), msb);
  }    
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