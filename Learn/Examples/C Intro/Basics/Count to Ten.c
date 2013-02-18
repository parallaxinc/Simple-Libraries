/*
  Count to Ten.c
  
  Count to ten in SimpleIDE Terminal.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Counting-Loops 
*/

#include "simpletools.h"

int main()                                    // Main function
{
  for(int n = 1; n <= 10; n++)                // Count to ten
  {
    pause(500);                               // 0.5 s between reps
    printf("n = %d\n", n);                    // Display name & value of n
  }
  printf("All done!");                        // Display all done
}
