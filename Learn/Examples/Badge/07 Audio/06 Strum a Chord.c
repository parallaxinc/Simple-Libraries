/*
  06 Strum a Chord.c
  Use 3 of the four available channels to play 3 notes simultaneously.
  C6 played for 1 s.  E6 added for the 2nd second, then G6 added for
  the 3rd and 4th seconds.
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("ch1,2,3 vols 64 ");              // Display channels/volumes
  sound_volume(audio, 0, 64);                 // Set channel volumes
  sound_volume(audio, 1, 64);
  sound_volume(audio, 2, 64);
  pause(1000);                                 // Wait 1 s
  
  clear();                                     // Clear oLED display
  oledprint("CH 0      C6    ");               // Display first ch/note
  sound_note(audio, 0, C6);                    // Play first note with ch 0
  pause(1000);                                 // ...for 1 s
  oledprint("CH 0 1    C6E6  ");               // Display second ch/note
  sound_note(audio, 1, E6);                    // Play second note with ch 1
  pause(1000);                                 // ...for 1 s
  oledprint("CH 0 1 2  C6E6G6");               // Display third ch/note
  sound_note(audio, 2, G6);                    // Play third note with ch 0
  pause(2000);                                 // ...for 1 s

  oledprint("CH 0 1 2   0 0 0");               // Display frequencies to 0
  sound_freq(audio, 0, 0);                     // Set all frequencies to 0
  sound_freq(audio, 1, 0);
  sound_freq(audio, 2, 0);
}

