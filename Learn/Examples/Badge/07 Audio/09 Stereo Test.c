/*
  09 Stereo Test.c
  Run 2 sound processes, one for each channel.  Play a brief tone in each
  ear, one from each process.  Then, create a tone that fades in volume and
  frequency from left to right. 
*/

#include "simpletools.h"                      // Library includes
#include "badgetools.h"
#include "sound.h"

sound *audioL, *audioR;                       // Pointers for audio processes

int main()                                    // Main function
{
  badge_setup();                              // Set up badge systems

  audioL = sound_run(9, -1);                  // Run left audio process
  audioR = sound_run(-1, 10);                 // Run right audio process
  
  oledprint("L               ");
  sound_note(audioL, 0, C4);                  // Play the C4 note on left
  pause(500);                                 // ...for 0.5 s
  sound_note(audioL, 0, 0);                   // Stop the note
  pause(100);                                 // ...for 0.1 s
  oledprint("       R        ");
  sound_note(audioR, 0, A4);                  // Play the C4 note on the right
  pause(500);                                 // ...for 0.5 s
  sound_note(audioR, 0, 0);                   // Stop the note
  pause(100);                                 // ...for 0.1 s
  oledprint("  FADE          ");
  
  screen_auto(OFF);                           // Auto-oLED update off for speed
  for(int v = 127; v > -1; v--)               // Vol fade L->R, f declines
  {
    line(127-v,32, 127-v, 64, 1);             // Draw white line
    screen_update();                          // Update display
    sound_freq(audioL, 0, 440 + v);           // Left frequency
    sound_freq(audioR, 0, 440 + v);           // Right frequency
    sound_volume(audioL, 0, v);               // Left volume
    sound_volume(audioR, 0, 127 - v);         // Right volume
    pause(20);                                // ...for 20 ms
    line(127-v,32, 127-v, 64, 0);             // Draw black line
    screen_update();                          // Update display
  } 
  for(int v = 127; v > -1; v--)               // Fade to 0 in right ear
  {                                           // f continues decline
    line(127, 64-(v/4), 127, 64, 1);          // Draw white line
    screen_update();                          // Update display
    sound_volume(audioR, 0, v);               // Right volume
    sound_freq(audioR, 0, 440 - 127 + v);     // Right frequency
    pause(20);                                // For 20 s
    line(127, 64-(v/4), 127, 64, 0);          // Draw black line
    screen_update();                          // Update display
  } 
}

