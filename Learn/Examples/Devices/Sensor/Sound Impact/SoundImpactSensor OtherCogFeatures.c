/*
  SoundImpactSensor OtherCogFeatures.c

  Expands on "SoundImpactSensor OtherCog" by demonstrating cog run 
  and end features.

  Connect: SIG to (R = 2.2 k) to P4, 5V to 5V, GND to GND 
  
  http://www.parallax.com/product/29132
*/

#include "simpletools.h"                      // Include simpletools
#include "soundimpact.h"                      // Include soundimpact

int main()                                    // Main function
{
  print("Tracks sound impacts and \n");       // User prompt
  print("updates every 3 seconds.\n");

  int *cog = soundImpact_run(4);              // Run in other cog

  // Check 10 times, every 3 seconds.
  for(int s = 0; s < 30; s += 3)              // Count to 30 in steps of 3        
  {
    int count = soundImpact_getCount();       // Get impact count
    print("count = %d\n", count);             // Display
    pause(3000);                              // Wait 3 seconds
  }

  print("Ending sound impact cog.\n");        // User info
  print("Cog is now free for other\n");
  print("process.\n");

  soundImpact_end(cog);                       // Stop sound impact cog
}

