/*
  Function Call.c
  
  Send a simple hello message to the console, but use a function to display
  one of the messages.
  
  learn.parallax.com/C/Propeller-C-Start-Simple/Reusable-Code-Functions
*/

#include "simpletools.h"                      // Include simpletools header

void hello(void);                             // Function prototype

int main()                                    // Main function
{
  pause(500);                                 // Pause 1/2 second
  hello();                                    // Call hello function
  printf("Hello again from main!\n");         // Display message
}

void hello(void)                              // Hello function
{
  printf("Hello from function!\n");           // Display hello message
  pause(500);                                 // Pause 1/2 second
}
