/*
  LIS3DH Test Resolution.c
  
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

  Notes:
  
  Resolution options are 8, 10 or 12-bit for accelerometer readings
                     and 8 or 10-bit for ADC readings
*/

#include "simpletools.h"                            // Include simpletools header
#include "lis3dh.h"                                 // Include lis3dh header 

lis3dh *LIS3DH;

int main()                                          // Main function
{
  
  pause(1000);                                      // Start-up pause for debug terminal
  term_cmd(CLS);
  term_cmd(HOME);
 
  print("Parallax LIS3DH 3 Axis Accelerometer module with ADC %c \r", CLREOL);
  print("Test Resolution Settings %c \r\r", CLREOL);
  
  
  int x, y, z;
  
  LIS3DH = lis3dh_init(8, 7, 6);                    // Initialize sensor with pins SCK, SDI, CS
   
  
  
  while(1) {                                        // Continuously read from sensor and print results to debug terminal
    
    // 8-bit      
    lis3dh_setResolution(LIS3DH, 8);
    
    if (lis3dh_accel(LIS3DH, &x, &y, &z)) {         // XYZ Data Available
                
        print("  resolution =  %00d bit : x = %d, y = %d, z = %d %c \r\r", 
              lis3dh_getResolution(LIS3DH), 
              x, y, z, CLREOL );                    // Display measurements
          
    } else { 
    
        print("No 8-bit xyz data %c \r\r", CLREOL ); 
        
    }
    
    
    // 10-bit      
    lis3dh_setResolution(LIS3DH, 10);
    
    if (lis3dh_accel(LIS3DH, &x, &y, &z)) {         // XYZ Data Available
                
        print("  resolution = %00d bit : x = %d, y = %d, z = %d %c \r\r", 
              lis3dh_getResolution(LIS3DH), 
              x, y, z, CLREOL );                    // Display measurements
          
    } else { 
    
        print("No 10-bit xyz data %c \r\r", CLREOL ); 
        
    }
    
    
    // 12-bit      
    lis3dh_setResolution(LIS3DH, 12);
    
    if (lis3dh_accel(LIS3DH, &x, &y, &z)) {         // XYZ Data Available
                
        print("  resolution = %00d bit : x = %d, y = %d, z = %d %c \r\r", 
              lis3dh_getResolution(LIS3DH), 
              x, y, z, CLREOL );                    // Display measurements
          
    } else { 
    
        print("No 12-bit xyz data %c \r\r", CLREOL ); 
        
    }
    



    pause(500);                                     // 1/2 second pause before repeat
    
    print("%c%c%c%c%c%c", 
    CRSRUP, CRSRUP, CRSRUP, 
    CRSRUP, CRSRUP, CRSRUP);                        // Terminal up six lines
   

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





