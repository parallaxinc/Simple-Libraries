/* Volts-Conversion.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"

int main()                                    // Main function
{
  // scale not working yet
  // da_useScale();                           // Get scale factors
  print("For 0.0 to 3.2 V D/A,\n");           // User instructions
  print("type your numbers as #.##\n");
  print("Then, press Enter.\n\n");
  float voltsOut, voltsIn;                    // Voltage variables
  while(1)
  {
    print("Enter D/A0 volts: ");              // Get voltage
    scan("%f\n", &voltsOut);
    da_volts(0, voltsOut);                    // Set volts
    voltsIn = ad_volts(0);                    // Measure volts
    print("voltsIn = %1.3f\n", voltsIn);      // Display measurement
  }
}