/*
  Multicore Example.c
  
  Launch a function into another cog (processor) and display what it does
  to the global n variable over time. 
  
  http://learn.parallax.com/propeller-c-functions/multicore-example
*/

#include "simpletools.h"                      // Include simpletools

void adder(void *par);                        // Forward declaration

static volatile int t, n;                     // Global vars for cogs to share
unsigned int stack[44 + 128];                 // Stack vars for other cog

int main()                                    // main function
{
  t = 50;                                     // Set values of t & n
  n = 5000;

  // Launch adder function into another cog (processor).
  cogstart(adder, NULL, stack, sizeof(stack));

  // Watch what the other cog is doing to the value of n.
  while(1)
  {
    print("n = %d\n", n);                     // Display result
    pause(100);                               // Wait 1/10 of a second    
  }    
}

// Function that can continue on its 
// own if launched into another cog.
void adder(void *par)                         // Adder keeps going on its own
{
  while(1)                                    // Endless loop
  {
    n = n + 1;                                // n + 1 each time loop repeats
    pause(t);                                 // Wait for t ms between updates
  }                            
}
