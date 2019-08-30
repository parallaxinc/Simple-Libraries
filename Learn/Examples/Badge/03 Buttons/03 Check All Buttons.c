/*
   Check All Buttons.c
   A variable with binary digits can store the bit pattern returned by
   the buttons function.  The leftmost bit-6 is the state of the OSH button.
   Pay close attention to the relationship of the 1's on the screen and the
   buttons you are pressing.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int states;                                  // For all button states

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup

  oledprint("BUTTONS");                      // Large display heading
  text_size(SMALL);                          // Switch to small text
  cursor(0, 4);                              // Small cursor row 4
  oledprint("PAD:   6543210");               // Display bit index
  cursor(0, 5);                              // Next line
  oledprint("STATE:");                       // Display state 
  cursor(0, 7);                              // Next line
  oledprint("EXIT: Press OSH");              // User prompt to exit
  
  while(1)                                   // States loop
  {
    states = buttons();                      // Load buttons output to states
    leds(states);                            // Light up corresponding LEDs
    
    cursor(7, 5);                            // Position cursor
    oledprint("%07b", states);               // Display states as binary number
    if(states == 0b1000000) break;           // If OSH pressed, exit loop
  }
  
  pause(400);                                 // Wait for 4/10 s

  text_size(LARGE);                           // Large text
  clear();                                    // Clear display
  oledprint("ALL DONE");                      // Done message
}


