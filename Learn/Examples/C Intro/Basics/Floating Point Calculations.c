/*
  Floating Point Calculations.c

  Version 0.94 for use with SimpleIDE 9.40 and its Simple Libraries
  
  Calculate and display circumference of a circle of radius = 1.0.
  
  http://learn.parallax.com/propeller-c-start-simple/floating-point-math
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  float r = 1.0;                              // Set radius to 1.0
  float c = 2.0 * PI * r;                     // Calculate circumference
  print("circumference = %f \n", c);          // Display circumference
}
