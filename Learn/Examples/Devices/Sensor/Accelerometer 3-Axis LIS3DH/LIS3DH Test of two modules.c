/*
  LIS3DH Test of two modules.c
  
  http://learn.parallax.com/propeller-c-simple-devices/lis3dh-three-axis-accelerometer
 
  I/O Pins connections: 
  
  Parallax LIS3DH Module 1
  P8  -> CLK      (SCK)
  P7 <-> DATA     (SDI)
  P6  -> /ENABLE  (CS) 
  
  Parallax LIS3DH Module 2
  P8  -> CLK      (SCK)
  P7 <-> DATA     (SDI)
  P5  -> /ENABLE  (CS) 
  
  Instructions:
  
  Connect two LIS3DH modules to Propeller using the pins shown above
  Also connect 3.3V and GND to the LIS3DH modules
  Upload this code to the Propeller
  Open SimpleIDE Terminal or Parallax Serial Terminal at 115200 baud to view the output
*/

#include "simpletools.h"                            // Include simpletools header
#include "lis3dh.h"                                 // Include lis3dh header 

lis3dh *LIS3DH_a, *LIS3DH_b;

int main()                                          // Main function
{
  
  pause(1000);                                      // Start-up pause for debug terminal
  term_cmd(CLS);
  term_cmd(HOME);
 
  print("Parallax LIS3DH 3 Axis Accelerometer module with ADC %c \r", CLREOL);
  print("Test Acceleration from two modules %c \r\r", CLREOL);
  
    
  int x, y, z;
  
  LIS3DH_a = lis3dh_init(8, 7, 6);
  LIS3DH_b = lis3dh_init(8, 7, 5);                  // different cs pin required!
 
  
  while(1) {                                        // Continuously read from sensor and print results to debug terminal
          
    
    if (lis3dh_accel(LIS3DH_a, &x, &y, &z)) {       // XYZ Data Available
                
        print("A : x = %d, y = %d, z = %d %c \r", 
              x, y, z, CLREOL );                    // Display measurements
          
    } else { 
    
        print("A : No xyz data %c \r\r", CLREOL ); 
        
    }
    
    
    
    if (lis3dh_accel(LIS3DH_b, &x, &y, &z)) {        // XYZ Data Available
                
        print("B : x = %d, y = %d, z = %d %c \r", 
              x, y, z, CLREOL );                     // Display measurements
          
    } else { 
    
        print("B : No xyz data %c \r\r", CLREOL ); 
        
    }
    
    
    pause(500);                                       // 1/2 second pause before repeat
    
    print("%c%c", CRSRUP, CRSRUP);                    // Terminal up two lines
    
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





