/*
  LIS3DH Test Temperature Sensor.c
  
  http://learn.parallax.com/propeller-c-simple-devices/lis3dh-three-axis-accelerometer
 
  I/O Pins connections: 
  
  P8  -> CLK      (SCK)
  P7 <-> DATA     (SDI)
  P6  -> /ENABLE  (CS)  
  
  Instructions:
  
  Connect LIS3DH module to Propeller using the pins shown above
  Also connect 3.3V and GND to the LIS3DH module
  Upload this code to the Propeller
  Open SimpleIDE Terminal or Parallax Serial Terminal at 115200 baud to view the output
  
  Notes about the Temperature Sensor:
  
  The LIS3DH chip includes an accurate relative temperature sensor, the output of which varies by 1 digit with each 1 degree Celcius change.
  To use the temperature sensor, it is necessary to record the ambient starting temperature, 
    which will be used by the sensor to calculate absolute temperature based on the relative output from the sensor. 
  Using Celcius is the most accurate unit, 
    as the sensor uses Celcius internally and therefore no temperature conversions are necessary which may result in conversion (rounding) errors.
  Wrapper functions are provided for Fahrenheit calibration and temperature reading, which convert the Celcius data available from the sensor.
*/

#include "simpletools.h"                            // Include simpletools header
#include "lis3dh.h"                                 // Include lis3dh header 

#define RoomTemperature_Degrees_Celcius 23          // Room temperature calibration value - Change this value to ambient (room) temperature!


lis3dh *LIS3DH;

int main()                                          // Main function
{
  
  pause(1000);                                      // Start-up pause for debug terminal
  term_cmd(CLS);
  term_cmd(HOME);
 
  print("Parallax LIS3DH 3 Axis Accelerometer module with ADC %c \r", CLREOL);
  print("Test Temperature Sensor %c \r\r", CLREOL);
  
  
  
  int t;
  
  LIS3DH = lis3dh_init(8, 7, 6);                    // Initialize sensor with pins SCK, SDI, CS
  
  
  // Set ambient (room) temperature - Use Celcius for best accuracy
  lis3dh_tempCal_C(LIS3DH, RoomTemperature_Degrees_Celcius);
  // lis3dh_tempCal_F(LIS3DH, RoomTemperature_Degrees_Fahrenheit);
  
   
  
  while(1) {                                        // Continuously read from sensor and print results to debug terminal
          
    
    print("Temperature is %dC, %dF %c \r", lis3dh_temp_C(LIS3DH), lis3dh_temp_F(LIS3DH), CLREOL);
    
    
    pause(500);                                     // 1/2 second pause before repeat
    
    print("%c", CRSRUP);                            // Terminal up one line
    
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





