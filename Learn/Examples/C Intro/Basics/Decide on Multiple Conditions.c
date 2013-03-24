/*
  Decide on Multiple Conditions.c 
  
  Make a decision based on two conditions.  
  
  http://learn.parallax.com/propeller-c-start-simple/make-complicated-decisions 
*/

#include "simpletools.h"                      // Include simpletools header

int main()                                    // main function
{
  pause(1000);                                // Wait 1 s for computer connection
  int a = 100;                                // Initialize a variable to 25
  int b = 17;                                 // Initialize b variable to 17
  printf("a = %d, b = %d\n", a, b);           // Print all
  if((a > b) && (a == 100))                   // If a > b AND A == 100
  {
    printf("a is larger than b,\n");          // Then print this message
    printf("AND a is 100!\n");                // Then print this message
  }
}
