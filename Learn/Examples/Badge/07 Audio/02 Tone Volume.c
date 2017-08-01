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
  
  oledprint("f=880Hz vol=127 ");              // Display frequency, volume
  sound_freq(audio, 0, 880);                  // Play 880 Hz frequency
  pause(1500);                                // ...for 1.5 s

  oledprint("f=880Hz vol=064 ");              // Display frequency, volume
  sound_volume(audio, 0, 64);                 // Set volume to 64
  pause(1500);                                // ...for 1.5 s

  oledprint("f=880Hz vol=032 ");              // Display frequency, volume
  sound_volume(audio, 0, 32);                 // Set volume to 32
  pause(1500);                                // ...for 1.5 s

  oledprint("f=880Hz vol=127 ");              // Display frequency, volume
  sound_volume(audio, 0, 127);                // Volume back to default
  pause(1500);                                // ...for 1.5 s

  oledprint("f=880Hz vol=000 ");              // Display frequency, volume
  sound_volume(audio, 0, 0);                  // Volume to 0
}

