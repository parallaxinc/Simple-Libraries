/*
  Measure Volts.c

  Make voltmeter style measurements with the Propeller Activity Board.

  http://learn.parallax.com/propeller-c-simple-circuits/measure-volts
*/

#include "simpletools.h"                      // Include simpletools
#include "adcDCpropab.h"                      // Include adcDCpropab

int main()                                    // Main function
{
  adc_init(21, 20, 19, 18);                   // CS=21, SCL=20, DO=19, DI=18

  float v2, v3;                               // Voltage variables

  while(1)                                    // Loop repeats indefinitely
  {
    v2 = adc_volts(2);                        // Check A/D 2                
    v3 = adc_volts(3);                        // Check A/D 3
    
    putChar(HOME);                            // Cursor -> top-left "home"
    print("A/D2 = %f V%c\n", v2, CLREOL);     // Display volts
    print("A/D3 = %f V%c\n", v3, CLREOL);     // Display volts

    pause(100);                               // Wait 1/10 s
  }  
}
