/* Volts-ControlledLED.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"

int main()                                    // Main function
{
  float volts;
  print("Use knob to control P26 light.");    // User prompt
  while(1)
  {
    volts = ad_volts(2);                      // Measure potentiometer
    da_volts(0, volts);                       // Set volts & light
  }
}