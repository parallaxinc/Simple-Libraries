/*
  Process Instances from One Function.c
  
  Advanced Topic: Demonstrates how to make multipe cogs run the same function's code.
  Each cog's process is defined by data in an instance of a structure.  The cogstart
  function passes that structure's address to the bunction using a par prameter, and
  the function accesses the data through that address.

  http://learn.parallax.com/propeller-c-multicore-approaches/multi-process-instances
*/

#include "simpletools.h"                      // Library include

void blink(void *par);                        // Forward delcare blink function

int stack1[43 + 20];                          // Stack space for each cog
int stack2[43 + 20]; 

int cog1;                                     // CogID variables for each cog
int cog2;

struct blink_st                               // Structure for process data
{
  int pin;                                    // Pin element
  int dt;                                     // Time increment element
};

int main()                                    // Main function
{
  struct blink_st blink1 = {26, 100};         // Two instances of the structure
  struct blink_st blink2 = {27, 50};

  // Start running blink function code in two different cogs.  Each instance
  // gets the address of a different structure.
  cog1 = cogstart(&blink, &blink1, stack1, sizeof stack1);
  cog2 = cogstart(&blink, &blink2, stack2, sizeof stack2);

  pause(2000);                                // Wait for two seconds

  blink1.dt = 50;                             // Change dt elements in both 
  blink2.dt = 25;                             // structures.

  pause(2000);                                // Wait another 2 seconds

  cogstop(cog1);                              // Stop both processes
  cogstop(cog2); 
}

void blink(void *par)                         // Function for other cog
{
  // Use structure address passed to par to set up a share pointer for whatever 
  // instance of blink gets cogstart-ed.  share->pin and share->dt are values 
  // of elements in the structure at the address stored by the share pointer.
  struct blink_st *share = (struct blink_st *) par;

  while(1)                                    // Main loop
  {
    high(share->pin);                         // Set pin high
    pause(share->dt);                         // Wait time increment
    low(share->pin);                          // Set pin low
    pause(share->dt);                         // Wait time increment
  }
}
