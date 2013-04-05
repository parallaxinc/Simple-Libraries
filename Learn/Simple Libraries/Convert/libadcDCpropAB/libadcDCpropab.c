/*
  libadcPropABdc.c
  Propeller Activity Board Simple Library project for DC measurements.
*/

#include "simpletools.h"                      // Include simpletools
#include "adcDCpropab.h"                      // Include adcPropABdc

int main()                                    // Main function
{
  pause(1000);                                // Wait 1 s for Terminal app
  adc_init(21, 20, 19, 18);                   // CS=21, SCL=20, DO=19, DI=18

  int i = 0;                                  // Index variable
  while(1)                                    // Loop repeats indefinitely
  {
    if(i == 4)                                // After index = 3
    {
      i = 0;                                  // Reset to zero
      printf("%c", HOME);                     // Cursor home
    }  
    printf("adc[%d] = %d%c\n", i,             // Display raw ADC
            adc_in(i), CLREOL); 
    printf("volts[%d] = %f%c\n\n",            // Display volts
           i, adc_volts(i), CLREOL); 
    i++;                                      // Add 1 to index
    pause(100);                               // Wait 1/10 s
  }  
}
