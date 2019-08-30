/*
  07 Different Waveforms.c
  Play the C6 note as sine, triangle, square and saw waves.  These names come
  from the way the voltage variations that create the sounds look when displayed
  over time on an oscilloscope.
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  
  oledprint("C6 waves   SINE ");              // Display waveform is sine
  sound_wave(audio, 0, SINE);                 // Set waveform to sine
  sound_note(audio, 0, C6);                   // Play note
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Frequency -> 0
  pause(1000);                                // ...for 1 s

  oledprint("C6 wavesTRIANGLE");              // Display waveform is triangle
  sound_wave(audio, 0, TRIANGLE);             // Set waveform to triangle
  sound_note(audio, 0, C6);                   // Play note
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Frequency -> 0
  pause(1000);                                // ...for 1 s

  oledprint("C6 waves SQUARE ");              // Display waveform is square
  sound_wave(audio, 0, SQUARE);               // Set waveform to square
  sound_note(audio, 0, C6);                   // Play note
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Frequency -> 0
  pause(1000);                                // ...for 1 s

  oledprint("C6 waves   SAW  ");              // Display waveform is saw
  sound_wave(audio, 0, SAW);                  // Set waveform to saw
  sound_note(audio, 0, C6);                   // Play note
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Frequency -> 0
  pause(1000);                                // ...for 1 s

  oledprint("f = 0           ");              // Display frequency to 0
  sound_freq(audio, 0, 0);                    // Set frequency to 0
}

