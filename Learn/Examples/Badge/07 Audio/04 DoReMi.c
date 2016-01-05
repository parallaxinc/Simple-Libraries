/*
  04 DoReMi.c
  C major solfege in the 5th octave.
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("CH  = 0 NOTE=C5 ");              // Display Ch and note
  sound_note(audio, 0, C5);                   // Play ch and note
  pause(250);
  oledprint("CH  = 0 NOTE=D5 ");              // Repeat for octave
  sound_note(audio, 0, D5);
  pause(250);
  oledprint("CH  = 0 NOTE=E5 ");
  sound_note(audio, 0, E5);
  pause(250);
  oledprint("CH  = 0 NOTE=F5 ");
  sound_note(audio, 0, F5);
  pause(250);
  oledprint("CH  = 0 NOTE=G5 ");
  sound_note(audio, 0, G5);
  pause(250);
  oledprint("CH  = 0 NOTE=A5 ");
  sound_note(audio, 0, A5);
  pause(250);
  oledprint("CH  = 0 NOTE=B5 ");
  sound_note(audio, 0, B5);
  pause(250);
  oledprint("CH  = 0 NOTE=C6 ");              // Up an octave   
  sound_note(audio, 0, C6);
  pause(500);
  oledprint("CH  = 0  f  = 0 ");              // Sound off
  sound_freq(audio, 0, 0);
}

