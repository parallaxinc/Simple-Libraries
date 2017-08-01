/*
  Two Tones Mixed.c
  Two sine waves added together create a warble called beat frequency.  The 
  rate of the beat frequency is equal do the difference in the two sine wave
  frequencies.  This example starts with channel 1 at 1047 Hz (C6 note) , then
  adds channel 2 at values of 1048, 1049, 1051, 1055, and 1063 for 1, 2, 4, 8,
  and 16 Hz warbles (beat frequencies).
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("Volumes CH1/2 64");              // Display volumes
  sound_volume(audio, 0, 64);                 // Set volumes
  sound_volume(audio, 1, 64);
  pause(500);                                 // Wait .5 s
  
  oledprint("f1=1047 f2=1048 ");              // Display freqs 1 Hz difference
  sound_freq(audio, 0, 1047);                 // 1 Hz warble
  sound_freq(audio, 1, 1048);
  pause(3000);                                // ...for 3 s
  
  oledprint("f1=1047 f2=1049 ");              // Display freqs 2 Hz difference
  sound_freq(audio, 0, 1047);                 // 2 Hz warble
  sound_freq(audio, 1, 1049);
  pause(3000);                                // ...for 3 s
  
  oledprint("f1=1047 f2=1051 ");              // Display freqs 4 Hz difference
  sound_freq(audio, 0, 1047);                 // 4 Hz warble
  sound_freq(audio, 1, 1051);
  pause(3000);                                // ...for 3 s
  
  oledprint("f1=1047 f2=1055 ");              // Display freqs 8 Hz difference
  sound_freq(audio, 0, 1047);                 // 8 Hz warble
  sound_freq(audio, 1, 1055);
  pause(3000);                                // ...for 3 s
  
  oledprint("f1=1047 f2=1063 ");              // Display freqs 16 Hz difference
  sound_freq(audio, 0, 1047);                 // 16 Hz warble
  sound_freq(audio, 1, 1063);
  pause(3000);                                // ...for 3 s
  
  oledprint("f1 = 0  f2 = 0  ");              // Display 0 frequencies
  sound_freq(audio, 0, 0);                    // Set frequencies to 0
  sound_freq(audio, 1, 0);
}

