/**
 * @file libLSM9DS1.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2016. All Rights MIT Licensed.
 *
 * @brief Test harness for the Propeller C library for the Parallax 9-axis IMU Sensor, based
 * on the STMicroelectronics LSM9DS1 inertial motion sensor chip.
 */


#include "lsm9ds1.h"
#include "simpletools.h"

#define SCL_PIN       6
#define SDIO_PIN      7
#define CS_AG_PIN     8
#define CS_M_PIN      9
#define INT_AG_PIN    10
#define INT_M_PIN     11
#define VCC_PIN       5
#define GND_PIN       4

#define RED_LED_PIN   15
#define YLW_LED_PIN   14
#define GRN_LED_PIN   13

#define BUTTON_PIN    0


//#define TEST_HARNESS    1



int gx, gy, gz; // x, y, and z axis readings of the gyroscope
int ax, ay, az; // x, y, and z axis readings of the accelerometer
float mx, my, mz;
float tmp;
int timeout_monitor;


int main() {
  
//#ifdef TEST_HARNESS

  while(1) 
  {
  
    //set the test_result variable to 0.
    //bits: [0][magInt][accelInt][magOut][accelOut][gyroOut][whoAmI][shorts]
    int test_result = 0b00000000;
  
    //set all of the IMU pins to High-Z
    input(VCC_PIN);
    input(GND_PIN);
    input(SCL_PIN);
    input(SDIO_PIN);
    input(CS_AG_PIN);
    input(CS_M_PIN);
    input(INT_AG_PIN);
    input(INT_M_PIN);
  
    //set the button to be an input
    input(BUTTON_PIN);
    
    //wait for a button press, then wait to debounce
    while(input(BUTTON_PIN));
    pause(100);
  
    //set green & red LEDs to OFF, yellow ON
    print("Testing.");
    low(RED_LED_PIN);
    high(YLW_LED_PIN);
    low(GRN_LED_PIN);
    
    //TODO test for shorts between pins?
    //---------------------------------------
    test_result |= 0b00000001;
    //---------------------------------------
    
    //power the module
    high(VCC_PIN);
    low(GND_PIN);
    
    //initialize the IMU, get the whoAmI response
    int whoAmI = imu_init(SCL_PIN, SDIO_PIN, CS_AG_PIN, CS_M_PIN);
    
    print(".");
    if(whoAmI == 0x683D) test_result |= 0b00000010;
    
    //3-axis tests
    //bits: [z-axis][y-axis][x-axis]
    int axis_result = 0b000;

    if(test_result == 0b00000011) {
      //test the gyro  
      //mark the system clock
      timeout_monitor = CNT;
      
      //read the gyro
      imu_setGyroScale(245);               //most sensitive setting
      pause(50);
      imu_readGyro(&gx, &gy, &gz);
      print(".");
      while(timeout_monitor < (CNT + CLKFREQ/250)) {
        
        //read the gyro
        imu_readGyro(&ax, &ay, &az);
        
        //test for different results - if the sensor is working, there should be slight variations between readings
        if(ax != gx) axis_result |= 0b001;
        if(ay != gy) axis_result |= 0b010;
        if(az != gz) axis_result |= 0b100;
        
        //if all outputs pass, pass the gyro
        if(axis_result == 0b111) {
          test_result |= 0b00000100;
          break;
        }      
      }
    }      

    if(test_result == 0b00000111) {    
      //test the accel 
      axis_result = 0b000;
      
      //read the accel
      imu_setAccelScale(2);                //most sensitive setting
      pause(50);
      imu_readAccel(&gx, &gy, &gz);
      print(".");
    
      //mark the system clock
      timeout_monitor = CNT + CLKFREQ;
    
      //keep checking until timeout or true
      while(timeout_monitor > CNT) {
        
        //read the accel again
        imu_readAccel(&ax, &ay, &az);
        
        //test for different results - if the sensor is working, there should be slight variations between readings
        if(ax != gx) axis_result |= 0b001;
        if(ay != gy) axis_result |= 0b010;
        if(az != gz) axis_result |= 0b100;
        
        //if all outputs pass, pass the accel
        if(axis_result == 0b111) {
          test_result |= 0b00001000;
          break;
        }      
      }
    }      
    
    if(test_result == 0b00001111) {
      //test the mag 
      axis_result = 0b000;
      
      //read the mag
      imu_setMagScale(4);                //most sensitive setting
      pause(50);
      imu_readMag(&gx, &gy, &gz);
      print(".");
    
      //mark the system clock
      timeout_monitor = CNT + CLKFREQ;
    
      //keep checking until timeout or true
      while(timeout_monitor > CNT) {
        
        //read the mag again
        imu_readMag(&ax, &ay, &az);
        
        //test for different results - if the sensor is working, there should be slight variations between readings
        if(ax != gx) axis_result |= 0b001;
        if(ay != gy) axis_result |= 0b010;
        if(az != gz) axis_result |= 0b100;
        
        //if all outputs pass, pass the mag
        if(axis_result == 0b111) {
          test_result |= 0b00010000;
          break;
        }      
      }
    }      
  
    if(test_result == 0b00011111) {
      //test the AG interrupt pin
      axis_result = 0b000;
      
      //clear accelerometer interrupts
      imu_clearAccelInterrupt();
      pause(50);
      print(".");
      if(!input(INT_AG_PIN)) axis_result |= 0b001;
       
      //set the accelerometer to interrupt if all axes less than 1.2g 
      imu_setAccelInterrupt(ALL_AXIS, 1.2, 20, 0, 0);
    
      timeout_monitor = CNT + CLKFREQ;
    
      //keep checking until timeout or true
      while(timeout_monitor > CNT) {
        if(input(INT_AG_PIN)) axis_result |= 0b010;
        
        //if all outputs pass, pass the accel
        if(axis_result == 0b011) {
          test_result |= 0b00100000;
          break;
        }      
      }
    }      
    
    if(test_result == 0b00111111) {
      //clear magnetometer interrupts
      imu_clearMagInterrupt();
      
      //test the M interrupt pin
      axis_result = 0b000;
      print(".");
      
      //clear magnetometer interrupts
      imu_clearMagInterrupt();
      pause(50);
      if(!input(INT_M_PIN)) axis_result |= 0b001;
       
      //set the magnetometer to interrupt if y-axis (gravity) less than 1.2g 
      imu_setMagInterrupt(ALL_AXIS, 0.01, 1);
    
      //mark the system clock
      timeout_monitor = CNT + CLKFREQ;
    
      //keep checking until timeout or true
      while(timeout_monitor > CNT) {
        if(input(INT_M_PIN)) axis_result |= 0b010;
        
        //if all outputs pass, pass the accel
        if(axis_result == 0b011) {
          test_result |= 0b01000000;
          break;
        }      
      }
         
      //clear magnetometer interrupts
      imu_clearMagInterrupt();
    }      
  
    //report the result of the test
    low(YLW_LED_PIN);
    if(test_result == 0b01111111) {
      high(GRN_LED_PIN);
      print("Passed\r");
    } else {
      high(RED_LED_PIN);
      print("Failed Reason = %d\r", test_result);
    }  
  }
  
  
/*
  while(1) {
    imu_readGyroCalculated(&mx, &my, &mz);
    print("Gyro:\t%.2f\t%.2f\t%.2f\t", mx, my, mz);
  
    imu_readAccelCalculated(&mx, &my, &mz);  
    print("Accel:\t%.2f\t%.2f\t%.2f\t", mx, my, mz);
  
    imu_readMagCalculated(&mx, &my, &mz);
    print("Mag:\t%.2f\t%.2f\t%.2f\t", mx, my, mz);
    
    imu_readTempCalculated(&tmp, FAHRENHEIT);
    print("Temp:\t%.2f\r", tmp);
    pause(100);
    
   }
   
    if(input(10))
    {
      high(26);
      imu_readAccelCalculated(&ax, &ay, &az);  
      print("Accel:\t%.2f\t%.2f\t%.2f\r", ax, ay, az);
 
      pause(250);
    }      
    else 
    {
      low(26);
      pause(1);
    }    
    
*/
/*
    imu_readGyro(&gx, &gy, &gz);
    print("Gyro:\t%d\t%d\t%d\r", gx, gy, gz);
  
    imu_readAccel(&ax, &ay, &az);  
    print("Accel:\t%d\t%d\t%d\r", ax, ay, az);
  
    imu_readMag(&mz, &my, &mz);
    print("Mag:\t%d\t%d\t%d\r", mz, my, mz);
    
    imu_readTemp(&tmp);
    print("Temp:\t%d\r\r", tmp);
      
    pause(500);
  }
  

#endif
*/ 
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