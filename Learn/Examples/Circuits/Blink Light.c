/*
  Blink Light.c
  
  Blink light circuit connected to P26.
  
  http://learn.parallax.com/propeller-c-simple-circuits/blink-light
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  while(1)                                    // Endless loop
  {
    high(26);                                 // Set P26 I/O pin high
    pause(100);                               // Wait 1/10 second
    low(26);                                  // Set P26 I/O pin low
    pause(100);                               // Wait another 1/10 second
  }
}
