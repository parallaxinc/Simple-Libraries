/*
  SoundImpactSensor OtherCog.c

  Monitors and tracks number of sound impacts from another cog.  
  It's an extravagant use of a cog, but will simplify tracking if
  the application has enough cogs available.

  Connect: SIG to (R = 2.2 k) to P4, 5V to 5V, GND to GND 
  
  http://www.parallax.com/product/29132
*/

#include "simpletools.h"                      // Include simpletools
#include "soundimpact.h"                      // Include soundimpact

int main()                                    // Main function
{
  print("Tracks sound impacts and \n");       // User prompt
  print("updates every 3 seconds.\n");

  soundImpact_run(4);                         // Run in other cog

  while(1)                                    // Endless main loop
  {
    int count = soundImpact_getCount();       // Get impact count
    print("count = %d\n", count);             // Display
    pause(3000);                              // Wait 3 seconds
  }
}

