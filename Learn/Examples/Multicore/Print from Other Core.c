/*
  Print from Other Core.c
  
  Use print statement in a function running in a different cog.

  http://learn.parallax.com/multicore-approaches/print-different-core
*/

#include "simpletools.h"                    // Library include

void other();                               // Forward declaration
int *otherCog;                              // Global pointer for cog_run return

int main()                                  // Main function
{
  print("Cog 0 has the Talking Stick first... \n");   

  simpleterm_close();                       // Close SimpleIDE Terminal for this core
  otherCog = cog_run(other, 128);           // Run other function in another core
}

void other()                                // other function definition
{
  simpleterm_open();                        // Open SimpleIDE Terminal for this core
  print("...and now the other cog has it. \n");                           

  simpleterm_close();                       // Close SimpleIDE Terminal
  cog_end(otherCog);                        // Shut down this core  
}



