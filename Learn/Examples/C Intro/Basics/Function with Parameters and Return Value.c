/*
  Function with Parameters and Return Value.c
  
  Pass parameters to a function, let it do its job, and display the result
  it returns.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Function-Parameters-Return-Value
*/

#include "simpletools.h"                      // Include simpletools header

int adder(int a, int b);                      // Function prototype

int main()                                    // Main function
{
  pause(500);                                 // 1/2 second pause
  int n = adder(25, 17);                      // Call adder function
  printf("adder's result is = %d", n);        // Display adder function result
}

int adder(int a, int b)                       // adder function
{
  int c = a + b;                              // Add two values
  return c;                                   // Return the result
}
