/*
  Cog Stack Usage Test.c
  
  Test how many int variables the cog actually used.

  http://learn.parallax.com/multicore-approaches
*/

#include "simpletools.h"                     // Library includes
#include "stacktest.h"                  

void myCog();                                // Function prototype
int *cog;                                    // Cog process ID variable

volatile int elements = 20;                  // Elements for cog's array

int main()                                   // Main function
{
  cog = cog_runStackTest(myCog, 512);        // Run the cog test
  print("Please wait 2 seconds...\n");       // User prompt
  pause(2000);                               // Give time to put cog to work
  int stacksize = cog_endStackTest(cog);     // Get the result
  print("Stack int usage = %d.\n",           // Display result
        stacksize);
}

void myCog()                                 // Function running in other cog
{
  int array[elements];                       // Declare an array
  int n = 0;                                 // Initialize counting variable
  while(1)                                   // Function's loop
  {
    array[n % elements] = n++;               // Add 1 to array cell, add 1 to n
    pause(10);                               // Wait 10 ms before repeat
  }
}
