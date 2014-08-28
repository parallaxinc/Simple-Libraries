/*
  Test MMA7455.c
  
  Test the Parallax MMA7455L 3 Axis Accelerometer module.

  http://learn.parallax.com/propeller-c-simple-devices/mma7455-three-axis-accelerometer
*/

#include "simpletools.h"                      // Include simpletools header
#include "mma7455.h"                          // Include mma7455 header 

short x, y, z;                                // Axis variables

int main()                                    // Main function
{
  
  MMA7455_init(7, 8, 6);                      // I/O to: DATA, CLK, /CS
  
  while(1)                                    // Main loop
  {

    MMA7455_getxyz10(&x, &y, &z);             // Get acceleration measurements
    print("%c x=%d, y=%d, z=%d  %c",          // Display measurements
           HOME, x,    y,    z, CLREOL);

    pause(200);                               // Wait 200 ms before repeat
  }
}

