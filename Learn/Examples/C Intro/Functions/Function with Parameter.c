/*
  Function with Parameter.c
  
  Call a function that displays a value passed to it with a parameter.
  
  http://learn.parallax.com/propeller-c-functions/function-parameter
*/

#include "simpletools.h"                      // Include simpletools

void value(int a);                            // Function prototype

int main()                                    // main function
{
  value(6);                                   // Call value function
}

void value(int a)                             // value function
{
  print("The value is: a = %d\n", a);         // Display a single value
}
