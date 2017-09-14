/*
   Say Hello Goodbye.c
   Say "hello" and "goodbye".  Note that the spelling in the talk_say 
   function calls is phonetic.  See Documentation text2speech Library.html 
   for a list of character strings for creating phonemes.
*/
                                                                                
#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library
#include "text2speech.h"                     // Include text2speech library

talk *spkr;                                  // Talk process ID/data pointer

void main()                                  // Main function
{
  badge_setup();                             // Start badge systems
  spkr = talk_run(9, 10);                    // Start talk process
  oledprint("Hello\n");                      // Display hello
  talk_say(spkr, "heloa");                   // Say hello
  pause(1500);                               // Pause for 1.5 s
  oledprint("Goodbye\n");                    // Display goodbye
  talk_say(spkr, "goodbae");                 // Say goodbye
}

