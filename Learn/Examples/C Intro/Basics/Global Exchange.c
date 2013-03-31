/*
  Global Exchange.c
  
  Functions exchange information with global variables. 
  
  learn.parallax.com/propeller-c-start-simple/memory-functions-can-share
*/

#include "simpletools.h"                      // Include simpletools

void adder(void);                             // Forward declaration

int a, b, n;                                  // Global variables

int main()                                    // main function
{
  pause(1000);                                // Wait 1 s for host
  a = 96;                                     // Set values of a & b
  b = 32;
  adder();                                    // Call adder function
  printf("n = %d\n", n);                      // Display result
}

void adder(void)                              // Adder, no parameters or return
{
  n = a + b;                                  // Use values of a & b to set n
}
