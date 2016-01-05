/*
   Send Data with IR.c
   This is the 'with structures' version of 00 Send Strings with IR.side.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

typedef struct info_st
{
  char name[16];
  char email[32];
} info;  

info education = {{"Education Staff"}, {"education@parallax.com"}};
info sales     = {{"Sales Staff"}, {"sales@parallax.com"}};
info support   = {{"Tech Support"}, {"support@parallax.com\n"}};

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  
  oledprint("IR Send");
  text_size(SMALL);
  cursor(0, 4);
  oledprint("P17 = Education\n");
  oledprint("P16 = Sales\n");
  oledprint("P15 = Support\n");
  
  while(1)
  {
    int states = buttons();
    if(states & 0b0111000)
    {
      rgbs(RED, RED);
    }      
    switch(states)
    {
      case 0b0100000:
        irprint("%16s\n%32s\n", education.name, education.email);
        break;
      case 0b0010000:
        irprint("%16s\n%32s\n", sales.name, sales.email);
        break;
      case 0b0001000:
        irprint("%16s\n%32s\n", support.name, support.email);
        break;
    }        
    if(states)
    {
      rgbs(OFF, OFF);
      pause(600);
    }      
  }      
}  
