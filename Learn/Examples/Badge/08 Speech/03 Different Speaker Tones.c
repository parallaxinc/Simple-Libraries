/*
   Different Speaker Tones.c
   Uses the talk_spell_speaker function to choose different speaker tones.
   Speakers can be numbered 0 to 9, though in this example, we have 0 to 3.
   To choose a tone, simply use #0, #1, #2 or #3 before the text in talk_say.
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library
#include "text2speech.h"                     // Include text2speech library

talk *spkr;                                  // Talk process ID/data pointer

void main()                                  // Main function
{
  badge_setup();                             // Start badge systems
  spkr = talk_run(9, 10);                    // Start talk process
  
  talk_set_speaker(spkr, 0, 80);             // Set up speaker tones
  talk_set_speaker(spkr, 1, 100);
  talk_set_speaker(spkr, 2, 120);
  talk_set_speaker(spkr, 3, 140);

  oledprint("Speaker ");                     // Display heading

  oledprint("0 ");                           // Display speaker number
  talk_say(spkr, "#0helloa");                // Test each speaker tone
  pause(100);                                // 0.1 s pause between each

  oledprint("1 ");                           // Repeat 3 more times
  talk_say(spkr, "#1helloa");
  pause(100);

  oledprint("2 ");
  talk_say(spkr, "#2helloa");
  pause(100);

  oledprint("3 ");
  talk_say(spkr, "#3helloa");
  pause(100);
}

