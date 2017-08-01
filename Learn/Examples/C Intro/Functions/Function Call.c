/*
  Function Call.c
  
  Send a simple hello message to the console, but use a function to display
  one of the messages.
  
http://learn.parallax.com/propeller-c-functions/reusable-code-functions
*/

#include "simpletools.h"                      // Include simpletools

void hello(void);                             // Function prototype

int main()                                    // main function
{
  hello();                                    // Call hello function
  print("Hello again from main!\n");          // Display message
}

void hello(void)                              // Hello function
{
  print("Hello from function!\n");            // Display hello message
  pause(500);                                 // Pause 1/2 second
}
