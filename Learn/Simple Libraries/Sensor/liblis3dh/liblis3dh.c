/*
  liblis3dh.c
  
  Test Harness for the Parallax LIS3DH 3 Axis Accelerometer module with ADC.

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
     
*/

#include "simpletools.h"      // Include simpletools header
#include "lis3dh.h"           // Include lis3dh header 


// Room temperature calibration value - Change this value to ambient (room) temperature!
#define RoomTemperature_Degrees_Celcius 23

lis3dh *LIS3DH;

int main()  // Main function
{
    
  int x, y, z, ax, ay, az, motion;
    
  pause(1000); // Start-up pause for debug terminal
  term_cmd(CLS);
  term_cmd(HOME);
      
  print("Demo code for Parallax LIS3DH Accelerometer %c \r", CLREOL);
    
  
  LIS3DH = lis3dh_init(8, 7, 6); // pinSCK, pinSDI, pinCS
  
    
  pause(100);
  
  print("%c \r", CLREOL);
  
  print("WhoAmI : %d (%s) %c \r\r", 
          lis3dh_getWhoAmI(LIS3DH), 
          (lis3dh_getWhoAmI(LIS3DH) == LIS3DH_WHO_AM_I_REPLY)? "OK":"ERROR", 
          CLREOL );
  
  lis3dh_setResolution(LIS3DH, 12); // 8, 10 or 12
  lis3dh_setRange(LIS3DH, 2); // 2, 4, 8 or 16
  
  lis3dh_tempCal_C(LIS3DH, RoomTemperature_Degrees_Celcius); // Set to ambient (room) temperature
  print("================================================================================ %c \r", CLREOL);
  print("Room temperature calibration is %dC. Change this value in the code if incorrect! %c \r", RoomTemperature_Degrees_Celcius, CLREOL);
  print("================================================================================ %c \r", CLREOL);
  
  print("%c \r", CLREOL);
  
  pause(100);
  
  print("Acceleration range is +-%dg, Resolution is %d bit %c \r\r", lis3dh_getRange(LIS3DH), lis3dh_getResolution(LIS3DH), CLREOL);


  
  //lis3dh_tiltConfig(LIS3DH, 75); // Set tilt sensor moving average factor (low-pass filter)
    
  
  while(1) {
    
    
    // XYZ and GForce
        
    if (lis3dh_accel(LIS3DH, &x, &y, &z)) { // Get raw acceleration data
      
      print("  Raw : x = %d, y = %d, z = %d %c \r", x, y, z, CLREOL );  // Display measurements
 
    } else { print("  Raw : data not ready %c \r", CLREOL ); }
    
    
    if (lis3dh_accel_mg(LIS3DH, &x, &y, &z)) { // Get acceleration data expressed as G-Force, in mg (milli-g)
      
      print("   mg : x = %d, y = %d, z = %d %c \r", x, y, z, CLREOL );  // Display measurements
 
    } else { print("   mg : data not ready %c \r", CLREOL ); }   
 
 
    // ADC
 
    lis3dh_adc(LIS3DH, &x, &y, &z); // Get adc values
    print("  adc : 1 = %d, 2 = %d, 3 = %d %c \r", x, y, z, CLREOL );  // Display measurements
    
    lis3dh_adc_mV(LIS3DH, &x, &y, &z); // Get adc values
    print("   mV : 1 = %d, 2 = %d, 3 = %d %c \r", x, y, z, CLREOL );  // Display measurements
    
    // Temperature
    
    print(" temp : %dC, sensor relative value is %d %c \r", lis3dh_temp_C(LIS3DH), lis3dh_tempRaw(LIS3DH), CLREOL);  // Display measurements
     
     
    // Angles
    if (lis3dh_tilt(LIS3DH, &ax, &ay, &az, &motion)) {
      
      print(" tilt : ax = %d, ay = %d, az = %d, motion = %d%c \r", ax, ay, az, motion, CLREOL );  // Display measurements
     
    } else { print(" tilt : data not ready %c \r", CLREOL ); } 
    
     
    // Debug terminal adjustment        
        
    print("%c%c%c%c%c%c", CRSRUP, CRSRUP, CRSRUP, CRSRUP, CRSRUP, CRSRUP); // Terminal up two lines, so results write back over same two lines when viewing on SimpleIDE Terminal or Parallax Serial Terminal 
        
        
    pause(250); // Minimum pause must be ODR * 2 in milliseconds (Examples: 50Hz ODR = 40ms pause, 400Hz ODR = 5ms pause)
        
        
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





