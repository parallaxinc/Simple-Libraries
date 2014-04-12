/*
  Set and Measure Volts.c

  Set D/A0 to 2.5 V and D/A1 to 1 V, and measure with A/D0 and A/D1.  

  http://learn.parallax.com/propeller-c-simple-circuits/set-volts
*/

#include "simpletools.h"                         // Include simpletools
#include "adcDCpropab.h"                         // Include adcDCpropab

int main()                                       // main function
{
  adc_init(21, 20, 19, 18);                      // CS=21, SCL=20, DO=19, DI=18

  dac_ctr(26, 0, 194);                           // D/A ch 0 -> 2.5 V to D/A 0
  dac_ctr(27, 1, 78);                            // D/A ch 1 -> 1 V to D/A 1

  print("A/D0 = %f\n", adc_volts(0));            // Display A/D0 volts
  print("A/D1 = %f\n", adc_volts(1));            // Display A/D1 volts
}


