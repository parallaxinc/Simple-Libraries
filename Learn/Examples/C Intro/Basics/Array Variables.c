/* 
  Array Variables.c  
   
  Declare and initialize an array and display a couple of its slements.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Array-Variables
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // Main function
{
  int p[] = {1, 2, 3, 5, 7, 11};              // Initialize the array
  pause(1000);                                // Wait 1 s for host
  printf("p[0] = %d\n", p[0]);                // Display what p[0] stores
  printf("p[3] = %d\n", p[3]);                // display what p[3] stores
}
