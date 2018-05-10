/* Volts-CalibrateDA.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"

int main() // Main function
{
  da_setupScale();                            // Calibration function
  print("Done!");                             // Done message
}