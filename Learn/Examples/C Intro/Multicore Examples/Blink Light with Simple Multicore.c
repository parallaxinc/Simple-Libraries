/*
  Blink Light with Simple Multicore.c   

  Multicore example for use with CMM or LMM memory models.

  http://learn.parallax.com/propeller-c-tutorials
*/

#include "simpletools.h"                      // Include simpletools library 

// For LMM cog 160 bytes declared as int
// Add enough for stack & calcs (50 bytes declared as int 
unsigned int stack[(160 + (50 * 4)) / 4];

// Declare volatile variables that will not be optimized
// to one variable for both cogs to share.
volatile unsigned int pin;
volatile unsigned int tdelay;

// Function prototype
void blink(void *par);

// Cog 0 starts here
int main()
{
  pin = 26;
  tdelay = 200;
  // Pass function pointer, optional parameter value, 
  // stack array address, and the stack's size to cogstart.
  int cog = cogstart(&blink, NULL, stack, sizeof(stack));
  // Cog 0 continues here
  pause(3000);
  // Cog 0 changes this global variable value that cog 1
  // uses to blink light. So, blink rate changes after 3 seconds.
  tdelay = 100;
  while(1);
}  

// Cog 1 starts executing code in this function in
// parallel.  Hooraaay!
void blink(void *par)
{
  while(1)
  {
    high(pin);
    pause(tdelay);
    low(pin);
    pause(tdelay);    
  }
}