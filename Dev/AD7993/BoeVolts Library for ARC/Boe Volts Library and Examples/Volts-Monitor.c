/* Volts-Monitor.c */

#include "simpletools.h"                      // Library includes
#include "boevolts.h"

int main()                                    // Main function
{
  float volts;
  while(1)
  {
    volts = ad_volts(2);                      // Get A/D2 volts
    print("%c A/D3 = %1.3f V ",               // Display result
    HOME, volts);
    pause(200);                               // 200 ms pause
  }
}