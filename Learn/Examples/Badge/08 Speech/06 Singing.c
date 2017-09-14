/*
   Singing.c
   Place C2 before a word to pronounce it using a pitch that's a C note
   in the second octave.  If next note is in the same octave (like D), it
   doesn't have to be followed by the octave digit.  Just make sure it's 
   upper-case.  For flat notes, follow the note letter with -, like E-.
*/

#include "simpletools.h"                      // Include simpletools library
#include "badgetools.h"                       // Include badgetools library
#include "text2speech.h"                      // Include text2speech library

talk *spkr;                                   // Talk process ID/data pointer

void main()                                   // Main function
{
  badge_setup();                              // Start badge systems
  spkr = talk_run(9, 10);                     // Start talk process
  
  oledprint("C Major\n");                     // Display scale C Major
  talk_say(spkr, "see m\'ayjer.");            // Say notes
  talk_say(spkr, "C2doa,Dray,Emee,Ffah,Gsoal,");
  talk_say(spkr, "Alah,Btee,C3d%200oa.");
  
  oledprint("C Minor");                       // Display scale C Minor
  talk_say(spkr, "see m\'aener.");            // Say notes
  talk_say(spkr, "C2doa,Dray,E-mee,Ffah,Gsoal,");
  talk_say(spkr, "A-lah,Btee,C3d%200oa.");
}

