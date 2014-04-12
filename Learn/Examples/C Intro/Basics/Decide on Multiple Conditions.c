/*
  Decide on Multiple Conditions.c 
  
  Make a decision based on two conditions.  
  
  http://learn.parallax.com/propeller-c-start-simple/make-complicated-decisions 
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  int a = 100;                                // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  print("a = %d, b = %d\n", a, b);            // Print all
  if((a > b) && (a == 100))                   // If a > b AND A == 100
  {
    print("a is larger than b,\n");           // Then print this message
    print("AND a is 100!\n");                 // Then print this message
  }
}
