/*
   Screen Character Sizes.c
   Use text_size function to switch from default LARGE characters to 
   small ones.  LARGE fits 8x2, SMALL fits 16x8.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  oledprint("BIG TEXT");                     // First message
  text_size(SMALL);                          // Enter small text mode
  cursor(0, 5);                              // Cursor to 5th small row
  oledprint("   Small Text.\n");             // Display some small text
  oledprint("More small text!");             // Note \n newline works
  pause(3000);                               // Delay 2 seconds
  text_size(LARGE);                          // Re-enter large text mode
  cursor(0, 1);                              // to sedon
  oledprint("        ");                     // Clear line 2
  cursor(2, 1);                              // Cursor near bottom-center
  oledprint("DONE");                         // Last message
}


