/*
  05 Flat Notes.c
  Play the 5th octave flat notes (black piano keys next between certain
  white keys from previous example program).
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("CH  = 0 NOTE=D5b");              // Display Ch and note
  sound_note(audio, 0, D5b);
  pause(500);
  oledprint("CH  = 0 NOTE=E5b");              // Display Ch and note
  sound_note(audio, 0, E5b);
  pause(500);
  oledprint("CH  = 0 NOTE=G5b");              // Display Ch and note
  sound_note(audio, 0, G5b);
  pause(500);
  oledprint("CH  = 0 NOTE=A5b");              // Display Ch and note
  sound_note(audio, 0, A5b);
  pause(500);
  oledprint("CH  = 0 NOTE=B5b");              // Display Ch and note
  sound_note(audio, 0, B5b);
  pause(500);
  oledprint("CH  = 0 F   = 0 ");              // Display Ch and note
  sound_freq(audio, 0, 0);
}

