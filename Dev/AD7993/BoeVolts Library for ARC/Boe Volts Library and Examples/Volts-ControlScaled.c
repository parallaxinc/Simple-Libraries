/* Volts-ControlScaled.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"

int x, y;

int main()                                    // Main function
{
  float volts;
  while(1)
  {
    x = ad_in (2);                            // Measure potentiometer
    print("%c x = %4d\n ",                    // Print input value (x)
    HOME, x);
    y = x * 256 / 2703;                       // Scale value
    print(" y = %4d\n ", y);                  // Print output value (y)
    da_out(0, y);                             // Set volts & light
    pause(200);                               // Slow data for terminal
  }
}