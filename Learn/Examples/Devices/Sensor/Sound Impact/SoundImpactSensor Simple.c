/*
  SoundImpactSensor Simple.c

  This sensor can be monitored repeatedly, and with a relatively small 
  interval to check for sounds.  The sensor's SIG pin sends a high signal
  if sound is detected, or a low if not.  Since SIG is connected to P4, 
  input(4) will return 1 if detected, or 0 if not.

  Connect: SIG to (R = 2.2 k) to P4, 5V to 5V, GND to GND 
  
  http://www.parallax.com/product/29132
*/

#include "simpletools.h"                          // Include simpletools

int main()                                        // Main function
{
  while(1)                                        // Main loop
  {
    print("%c", HOME);                            // Cursor -> top-left
    if(input(4))                                  // Sensor high (detected)
    {
      print("Sound impact detected!%c", CLREOL);  // Display detected message
      pause(1000);                                // Wait for user to see it
    }
    else                                          // Sensor low (not detected)
    {
      print("Waiting for sound...%c", CLREOL);    // Display waiting message
    }
    pause(50);                                    // Slow down for terminal
  }  
}
