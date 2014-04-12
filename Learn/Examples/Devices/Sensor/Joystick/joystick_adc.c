/*
  Joystick.c

  Simple Propeller P8X32A Propeller C demo with the Parallax 2-axis Joystick

  http://learn.parallax.com/propeller-c-simple-devices/joystick   
*/

#include "adcDCpropab.h"                            // Include adcDCpropab
#include "simpletools.h"                            // Include simpletools


int main()                                          // Main function
{
  pause(1000);                                      // Wait 1 s for Terminal app
  adc_init(21, 20, 19, 18);                         // CS=21, SCL=20, DO=19, DI=18

  float lrV, udV;                                   // Voltage variables

  while(1)                                          // Loop repeats indefinitely
  {
    udV = adc_volts(2);                             // Check A/D 2                
    lrV = adc_volts(3);                             // Check A/D 3
   
    putChar(HOME);                                  // Cursor -> top-left "home"
    print("Up/Down = %.2f V %c\n", udV, CLREOL);    // Display voltage
    print("Left/Right = %.2f V %c\n", lrV, CLREOL); // Display voltage

    pause(100);                                     // Wait 1/10 s
  }  
}

