/*
  Decision Chain.c
  
  Check a series of conditions, but only act on the first one that's true.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Decision-Chain
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  pause(1000);                                // Wait 1 s for computer connection
  int a = 25;                                 // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  printf("a = %d, b = %d\n", a, b);           // Print all
  if(a > b)                                   // If a > b condition is true
  {
    printf("a is larger \n");                 // Then print this message
  }
  else if (a < b)                             // a > b not true? check a < b
  {
    printf("b is larger \n");                 // If true, print this instead
  }
  else                                        // Nothing else true?
  {
    printf("a eqals b");                      // Print this
  }
}
