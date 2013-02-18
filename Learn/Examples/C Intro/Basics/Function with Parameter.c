/*
  Function with Parameter.c
  
  Call a function that displays the result of two values added together.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Function-Call-Parameter
*/

#include "simpletools.h"                      // Include simpletools header

void value(int a);                            // Function prototype

int main()                                    // Main function
{
  pause(500);                                 // Pause 1/2 second
  value(6);                                   // Call value function
}

void value(int a)                             // Value function
{
  printf("The value is: a = %d\n", a);         // Display a single value
}
