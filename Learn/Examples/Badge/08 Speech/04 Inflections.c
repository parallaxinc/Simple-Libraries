/*
   Inflections.c
   Certain characters can crate inflections.  For example, the ' increases
   increase the pitch for one phoneme, making kwest'yen sound like a question.
   Use Documentation text2speech Library.html to look up the rest of the 
   inflection marks used here.
*/

#include "simpletools.h"                        // Include simpletools library
#include "badgetools.h"                         // Include badgetools library
#include "text2speech.h"                        // Include text2speech library

talk *spkr;                                     // Talk process ID/data pointer

void main()                                     // Main function
{
  badge_setup();                                // Start badge systems
  spkr = talk_run(9, 10);                       // Start talk process
  
  talk_set_speaker(spkr, 0, 95);                // Set up two speakers
  talk_set_speaker(spkr, 1, 110);
  
  text_size(SMALL);                             // Display small text

  oledprint("Do you have a   question? ");      // Display subtitles
  talk_say(spkr, "#0doo yoo hav a kwest'yen."); // 0 asks question 
  oledprint("Yes, Ido. ");
  talk_say(spkr, "#1yes ae d'oo.");             // 1 answers o-o accented
  oledprint("Then ask it.");
  talk_say(spkr, "#0dhen, ask~ it.");           // Corrective, more k (kuh)
  oledprint("Can you hear m'e?");
  talk_say(spkr, "#1(kan yoo heeer m'ee.)");    // (whispers)
  oledprint("Yes, I can. ");
  talk_say(spkr, "#0yes ae kan.");               
  oledprint("Good");
  talk_say(spkr, "#1g//oo\\\\oo'd~.");          // Goo-oo-d(uh) w pitch up/dn
  oledprint("Talk faster. ");
  talk_say(spkr, "#0tok fastur.");              
  oledprint("Youmean like this? ");
  talk_say(spkr, "#1%50yoo meen laek th'is.%"); // 0.5 x time on each phoneme
  oledprint("I sure do. ");
  talk_say(spkr, "#0>>ae shoo'er <<<<d'oo.");   // Volume dn 2, up 4
  oledprint("Okay.");
  talk_say(spkr, "#1%400oa 'kay.%");            // 4 x time on each phoneme
}

