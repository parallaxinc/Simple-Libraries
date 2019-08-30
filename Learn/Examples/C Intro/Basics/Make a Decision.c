/*
  Make a Decision.c
  
  If a condition is true, display a second message.
  
  http://learn.parallax.com/propeller-c-start-simple/make-decision
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  int a = 25;                                 // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  print("a = %d, b = %d\n", a, b);            // Print all
  if(a > b)                                   // If a > b condition is true
  {
    print("a is larger \n");                  // ...then print this message
  }
}
