/*
  Test ColorPAL.c
  
  Test Parallax ColorPAL sensor.
  
  Connect: sig to P6, +5V to 5V, Gnd to GND
  
  http://www.parallax.com/product/28380
*/

#include "simpletools.h"                      // Include simpletools
#include "colorpal.h"                         // Include colorpal

colorPal *cpal;                               // Device identifier
int cpSIO = 6;                                // ColorPAL SIO -> Propeller P6
int r, g, b;                                  // Variables for red, green, blue

int main()                                    // Main function
{
  cpal = colorPal_open(cpSIO);                // Open connection to ColorPAL

  while(1)                                    // Main loop
  {
    colorPal_getRGB(cpal, &r, &g, &b);        // Get red/green/blue readings

    print("r = %04d g = %04d b = %04d\n",     // Display red/green/blue readings
           r,       g,       b);    

    pause(1000);                              // 1 s before repeat
  }
}
