/*
  PAM-7Q GPS Test.c

  Test PAM-7Q GPS module by detecting and displaying GPS fix status, latitude
  and longitude measurements.
  
  VDD -- 3.3V
  TXD -> P11
  RXD <- P10
  GND -- GND
  
  http://learn.parallax.com/propeller-c-simple-devices/
*/

#include "simpletools.h"                      // Include libraries
#include "gps.h"                              

#define GPS_TXD       11                      // GPS TX -> P11
#define GPS_RXD       10                      // GPS RX <- P10
#define GPS_BAUD      9600                    // Baud rate = 9600 bps

float latitude, longitude;                    // Latitude/longitude variables
int fix;                                      // GPS fix indicator variable

int main()                                    // Main function
{
  gps_open(GPS_TXD, GPS_RXD, GPS_BAUD);       // Open the GPS driver
  
  while(1)                                    // Main loop
  {
    latitude = gps_latitude();                // Get latitude
    longitude = gps_longitude();              // Get longitude
    fix = gps_fixValid();                     // Check for valid fix

    print("%c", HOME);                        // Send cursor to top-left HOME

    print("GPS Fix: ");                       // Display fix status
    if(fix)
      print("Valid     \n");
    else
      print("Not Valid \n");
      
    print("\nLatitude    Longitude\n");       // Display latitude/longitude
    print("%f  %f", latitude, longitude);

    pause(500);                               // Repeat in 1/2 second
  }
}

