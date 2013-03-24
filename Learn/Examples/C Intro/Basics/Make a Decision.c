/*
  Make a Decision.c
  
  If a condition is true, display a second message.
  
  http://learn.parallax.com/propeller-c-start-simple/make-decision
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  pause(1000);                                // Wait 1 s for computer connection
  int a = 25;                                 // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  printf("a = %d, b = %d\n", a, b);           // Print all
  if(a > b)                                   // If a > b condition is true
  {
    printf("a is larger \n");                 // ...then print this message
  }
}
