/*
  Index Array Variables.c
  
  Use a for loop to display all the elements in an array.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Index-Array-Variables
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  int p[] = {1, 2, 3, 5, 7, 11};              // Initialize the array
  for(int i = 0; i < 6; i++)                  // Count i from 0 to 6
  {
    pause(500);                               // 1/2 second pause
    printf("p[%d] = %d\n", i, p[i]);          // Display array element & value
  }
}
