/*
   Avoid Repeats.c
   The previous example program allows you to store the same information
   to EEPROM repeatedly.  If you'd prefer to have your program check before
   saving the data, use if(!stored...).  Here's an example.  Remember to 
   use SimpleIDE's Run with Terminal button to view the results. 
   
   You have already saved wilma and betty to EEPROM with the previous program.
   If this program did not use the if(!stored...) statements, you would end up
   with 6 contacts instead of just four.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

//   badge        num   name
char fred[]   = {"123\n Fred\n"};
char wilma[]  = {"456\n Wilma\n"};
char barney[] = {"789\n Barney\n"};
char betty[]  = {"147\n Betty\n"};

char their[16];                              // Array for retrieved strings

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  text_size(SMALL);    
  oledprint("Use SimpleIDE\nTerminal.");
  
  if(!stored(wilma))                         // Check first, if repeat skip
    store(wilma);
  if(!stored(betty)) 
    store(betty);
  if(!stored(fred))                          // ...but if not repeat, store
    store(fred);
  if(!stored(barney)) 
    store(barney);
    
  contacts_displayAll();                       // Display contacts
}  
