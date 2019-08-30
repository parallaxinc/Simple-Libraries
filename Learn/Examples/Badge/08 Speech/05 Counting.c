/*
   Counting.c
   Examples of pronouncing numbers with the talk_say function.
*/

#include "simpletools.h"                      // Include simpletools library
#include "badgetools.h"                       // Include badgetools library
#include "text2speech.h"                      // Include text2speech library

talk *spkr;                                   // Talk process ID/data pointer

void main()                                   // Main function
{
  badge_setup();                              // Start badge systems
  spkr = talk_run(9, 10);                     // Start talk process
  
  talk_set_speaker(spkr, 0, 95);              // Set up two speakers
  talk_set_speaker(spkr, 1, 110);
  
  text_size(SMALL);                           // Display small text

  // Say numbers (with subtitles on oLED display).
  oledprint("1,2,3,4,5,");                      
  talk_say(spkr, "wun~, too, three, for, faev,");
  oledprint("6,7,8,9,10,");
  talk_say(spkr, "siks, s\'even~, ayt, naen~, ten~,");
  oledprint("11,12,13,1415,");
  talk_say(spkr, "el\'even~, twelv, th\'irteen~, f\'orteen~, f\'ifteen~,");   
  oledprint("16,17,18,19,");
  talk_say(spkr, "s\'iksteen~, s\'eventeen~, \'aytteen~, n\'aenteen~,");
  oledprint(" 20,30,40,50,");
  talk_say(spkr, "tw\'entee, th\'irtee, f\'ortee, f\'iftee,");
  oledprint("60, 70,80,90,");
  talk_say(spkr, "s\'ikstee, s\'eventee,\'aytee, n\'aentee,");
  oledprint("100,");
  talk_say(spkr, "h\'undred,");
  oledprint("   1000, ");
  talk_say(spkr, "th\'ousand, ");
  oledprint("\n1,000,000");
  talk_say(spkr, "m\'ilyun~,");
  oledprint(",000");
  talk_say(spkr, "b\'ilyun~,");
  oledprint("    ,000");
  talk_say(spkr, "tr\'ilyun~,");
  oledprint(",000");
  talk_say(spkr, "kwodr\'ilyun~,");
  oledprint(",000");
  talk_say(spkr, "kwint\'ilyun~,...");
}

