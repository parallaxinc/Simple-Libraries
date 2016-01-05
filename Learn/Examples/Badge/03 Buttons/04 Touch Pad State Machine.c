/*
   Touch Pad State Machine.c
   Advance through various binary states of the state variable.  By pressing
   each button, all 7 binary digits will be 1, allowing the program to exit 
   the loop.  This example uses the logical OR operation to copy previous 
   button presses to the history variable.  When the history variable reaches
   0b1111111, all buttons have been pressed and the loop terminates.  
 */

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library

int history = 0, states = 0;                 // State machine variables

void main()                                  // Main function
{
  badge_setup();                             // Call badge setup
  // User prompts
  print("Touch pads to control blue lights!\n");
  print("To exit pad mode, touch all 7 pads\n\n");
  clear();                                   // Heading
  oledprint("TOUCHPAD");                     
  pause(500);                                // Delay
  text_size(SMALL);                          // Set text size small
  cursor(0, 5);                              // Position cursor
   
  // Another user prompt
  oledprint("Touch all 7 pads   (to finish)");  
   
  while(1)                                   // State machine loop
  {
    states = buttons();                      // Get button states
    history |= states;                       // OR 1s to history variable
    leds(history);
    // Light LEDs with history     
    if(history == 0b1111111) break;
    // Break from loop if all buttons     
    cursor(0, 7);                            // Position cursor
    oledprint("complete=%07b", history);     // Display history in binary   
  } 
   
  text_size(LARGE);                          // Display all done      
  cursor(0, 0);    
  oledprint("PADS    Done!   ");
  pause(800);
  leds(0b000000);                            // Lights off
}



