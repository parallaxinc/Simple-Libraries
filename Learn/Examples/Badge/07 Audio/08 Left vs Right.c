/*
  08 Left vs Right.c
  
  Run and end the sound process with different configurations.  First,
  both speaker channels, then just the right, then just the left.
  
  NOTE: The takeaway from this is supposed to be that you can use -1
        when starting a sound process to make only one of the two pin
        options actually send audio signals.  If you instead just need 
        to stop sound temporarily, set either the channel(s) volume(s)
        or frequency(ies) to 0(s).
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audio;                                 // Pointer for audio process

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audio = sound_run(9, 10);                   // Run sound, get audio pointer
  oledprint(" BOTH    SIDES  ");              // Display sound to both sides
  sound_freq(audio, 0, 440);                  // Play a frequency
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Set frequency to 0
  sound_end(audio);                           // End the audio process
  pause(200);                                 // Wait 0.2 s
  
  audio = sound_run(-1, 10);                  // Run sound on right speaker 
  oledprint("    JUST   RIGHT");              // Display just right
  sound_freq(audio, 0, 440);                  // Play a frequency
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Set frequency to 0
  sound_end(audio);                           // End audio process again
  pause(200);                                 // Wait 0.2 s

  audio = sound_run(9, -1);                   // Run sound on left speaker
  oledprint("JUST    LEFT    ");              // Display just left
  sound_freq(audio, 0, 440);                  // Play a frequency
  pause(1000);                                // ...for 1 s
  sound_freq(audio, 0, 0);                    // Set frequency to 0
  sound_end(audio);                           // End audio process yet again

  oledprint("  ALL     OFF   ");              // Display all off
}

