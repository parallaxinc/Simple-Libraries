/*
  Test Ping Distance.c
  
  Measure and display Ping))) Ultrasonic Distance Sensor distance measurements.
  
  http://learn.parallax.com/propeller-c-simple-devices/sense-distance-ping
*/

#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header

int main()                                    // main function
{
  while(1)                                    // Repeat indefinitely
  {
    int cmDist = ping_cm(15);                 // Get cm distance from Ping)))
    print("cmDist = %d\n", cmDist);           // Display distance
    pause(200);                               // Wait 1/5 second
  }
}

