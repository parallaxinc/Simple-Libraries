/* 
  Array Variables.c  

  Version 0.94 for use with SimpleIDE 9.40 and its Simple Libraries
   
  Declare and initialize an array and display a couple of its elements.
  
  http://learn.parallax.com/propeller-c-start-simple/array-variables
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  int p[] = {1, 2, 3, 5, 7, 11};              // Initialize the array
  print("p[0] = %d\n", p[0]);                 // Display what p[0] stores
  print("p[3] = %d\n", p[3]);                 // display what p[3] stores
}
