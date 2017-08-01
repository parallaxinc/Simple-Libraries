/*
  Index Array Variables.c
  
  Use a for loop to display all the elements in an array.
  
  http://learn.parallax.com/propeller-c-start-simple/index-array-variables
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  int p[] = {1, 2, 3, 5, 7, 11};              // Initialize the array
  for(int i = 0; i < 6; i++)                  // Count i from 0 to 5
  {
    print("p[%d] = %d\n", i, p[i]);           // Display array element & value
    pause(500);                               // 1/2 second pause
  }
}
