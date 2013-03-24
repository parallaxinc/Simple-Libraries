/*
  Repeat While.c
  
  Keep displaying n = n + 5 every half second while n <= 200.
  
  http://learn.parallax.com/propeller-c-start-simple/code-repeats
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  int n = 0;                                  // Declare n, initialize to zero
  while(n < 200)                              // Repeat while n less than 200
  {
    pause(500);                               // 0.5 s between repetitions
    n = n + 5;                                // Add 5 to n each time through
    printf("n = %d\n", n);                    // Display name & value of n
  }
  printf("All done!");                        // Display all done
}
