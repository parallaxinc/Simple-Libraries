/*
  Display Dial.c
  
  Display potentiometer in RC circuit connected to P5.
  
  http://learn.parallax.com/C/Simple-Circuits-Propeller-C/Check-Dial-Position
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  while(1)                                    // Endless loop
  {
    high(5);                                  // Set P5 high
    pause(1);                                 // Wait for circuit to charge
    long t = rcTime(5, 1);                    // Measure decay time on P5
    printf("t = %d\n", t);                    // Display decay time
    pause(100);                               // Wait 1/10th of a second
  }
}

