/*
  Count to Ten.c
  
  Count to ten in SimpleIDE Terminal.
  
  http://learn.parallax.com/propeller-c-start-simple/counting-loops
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  for(int n = 1; n <= 10; n++)                // Count to ten
  {
    pause(500);                               // 0.5 s between reps
    printf("n = %d\n", n);                    // Display name & value of n
  }
  printf("All done!");                        // Display all done
}
