/*
  Test Compass.c
  
  Test compass with SCL connected to P3 and SDA connected to P2. Display
  measurement results in SimpleIDE Terminal.
  
  http://learn.parallax.com/C/Simple-Devices-Propeller-C/Sense-Compass-Direction
*/

#include "simpletools.h"                      // Include simpletools header
#include "compass3d.h"                        // Include compass3d header

int main()                                    // Main function
{
  int x, y, z;                                // Declare x, y, & z axis variables
  
  i2c bus = i2c_newbus(3, 2);                 // New I2C bus SCL=P3, SDA=P2
  CompassInit(bus);                           // Initialize compass on bus.

  while(1)                                    // Repeat indefinitely
  {
    CompassRead(bus, &x, &y, &z);             // Compas vals -> variables
    printf("%cx=%d, y=%d, z=%d%c%c",          // Display compass variables
           HOME, x, y, z, CLREOL, CR);
    pause(500);                               // Wait 1/2 second
  }
}


