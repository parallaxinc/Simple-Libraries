/*
  Repeat at Least Once.c

  You can use do...while to make sure a loop executes at least once, even
  if the condition it uses for repeating is not true.  This program shows 
  how it works by displaying n = n + 5 every half second while n <= 10.  The
  loop works normally, but if you change it to while(n <= -10), it still 
  executes the code inside once even though the condition isn't true.  So, 
  you will see it display n = 0.  Also, by the time it gets to print("All
  done!"), n will store 5 because the code in the do...loop was executed
  once.
  
  http://learn.parallax.com/propeller-c-start-simple
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  int n = 0;                                  // Declare n, initialize to zero
  do                                          // Do the loop ended by while
  {
    print("n = %d\n", n);                     // Display name & value of n
    n = n + 5;                                // Add 5 to n each time through
    pause(500);                               // 0.5 s between repetitions
  }
  while(n <= 10);                             // Back to do if condition true
  print("All done!");                         // Display all done
}
