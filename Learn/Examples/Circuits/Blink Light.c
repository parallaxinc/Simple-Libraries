/*
  Blink Light.c
  
  Blink light circuit connected to P9.
  
  http://learn.parallax.com/C/Simple-Circuits-Propeller-C/Blink-Light
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  while(1)                                    // Endless loop
  {
    high(26);                                 // Set P26 I/O pin high
    pause(100);                               // Wait 1/10 second
    low(26);                                  // Set P26 I/O pin low
    pause(100);                               // Wait another 1/10 second
  }
}
