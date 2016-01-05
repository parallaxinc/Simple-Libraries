/*
  One Tone Two Seconds.c
  Run audio process configured to send audio to P9 (left) and P1 (right).
  Make audio process play 440 Hz sine wave (A note above middle C) for 2 s.
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("f = 440\n");                     // Display frequency
  sound_freq(audio, 0, 440);                  // Audio, channel 0, 440 Hz
  pause(2000);                                // For 2 seconds
  oledprint("f = 0\n");                       // Display new frequency
  sound_freq(audio, 0, 0);                    // Set frequency to 0 Hz
}

