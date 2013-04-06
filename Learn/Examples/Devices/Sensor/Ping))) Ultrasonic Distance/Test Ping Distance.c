/*
  Test Ping Distance.c
  
  Measure and display Ping))) Ultrasonic Distance Sensor distance measurements.
  
  http://learn.parallax.com/C/Simple-Devices-Propeller-C/Sense-Distance-Ping
*/

#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header

int main()                                    // Main function
{
  while(1)                                    // Repeat indefinitely
  {
    int cmDist = ping_cm(17);                 // Get cm distance from Ping)))
    printf("cmDist = %d\n", cmDist);          // Display distance
    pause(200);                               // Wait 1/2 second
  }
}

