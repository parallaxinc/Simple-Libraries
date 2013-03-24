/*
  Repeat at Least Once.c
  
  Keep displaying n = n + 5 every half second while n <= 10.
  Try making the while condition not true and see what happens.  For example
  change it to while(n < 0), which will not happen here.  Note that the code 
  in the loop still gets executed once.
  
  http://learn.parallax.com/propeller-c-start-simple/repeat-least-once
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  pause(1000);
  int n = 0;                                  // Declare n, initialize to zero
  do                                          // Do the loop ended by while
  {
    pause(500);                               // 0.5 s between repetitions
    n = n + 5;                                // Add 5 to n each time through
    printf("n = %d\n", n);                    // Display name & value of n
  }
  while(n < 10);                              // Back to do if condition true
  printf("All done!");                        // Display all done
}
