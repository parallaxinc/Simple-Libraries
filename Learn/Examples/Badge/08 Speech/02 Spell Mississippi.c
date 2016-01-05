/*
   Spell Mississippi.c
   Uses the talk_spell function to sound out letters.  Remember that spelling
   in the talk_say function calls is phonetic and that for a list of character
   strings for creating phonemes is in Documentation text2speech Library.html.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library
#include "text2speech.h"                     // Include text2speech library

talk *spkr;                                  // Talk process ID/data pointer

void main()                                  // Main function
{
  badge_setup();                             // Start badge systems
  spkr = talk_run(9, 10);                    // Start talk process
  talk_say(spkr, "ae kan spell misisipee."); // I can spell Mississippi
  pause(300);                                // Pause for 0.3 s
  oledprint("MISSISS-IPPI    ");             // Display Mississippi
  talk_spell(spkr, "mississippi");           // Spell Mississippi
  pause(300);                                // Pause another 0.3 s
  talk_say(spkr, "misisipee.");              // Say Mississippi
  oledprint("  Very    Good  ");             // Display "Very Good"
}

