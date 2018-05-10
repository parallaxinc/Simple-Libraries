/* Volts-DividerVoltage.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"                          // Must include to use abvolts

int main()                                    // Main function
{
  float volts = ad_volts(2);                  // Get A/D3 volts
  print("A/D2 = %1.3f V\n", volts);           // Display result
  print("\nDone!");                           // Announce program done
}