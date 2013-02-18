/*
  Variables and Calculations.c
  
  Add two integer values together and display the result.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Variables-Calculations
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  pause(1000);                                // Wait 1 s for host computer
  int a = 25;                                 // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  int c = a + b;                              // Initialize c variable to a + b
  printf("c = %d\n ", c);                     // Display decimal value of c
}
