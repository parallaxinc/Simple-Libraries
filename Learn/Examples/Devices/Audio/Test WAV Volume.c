/*
  Test WAV Volume.c

  Play back a .wav file and try a few different volume settings.   
  
  http://learn.parallax.com/propeller-c-simple-devices/play-wav-files
*/

#include "simpletools.h"
#include "wavplayer.h"
    
int main()                                        // main function
{
  int DO = 22, CLK = 23, DI = 24, CS = 25;        // SD I/O pins
  sd_mount(DO, CLK, DI, CS);                      // Mount SD card
 
  const char techloop[] = {"techloop.wav"};       // Set up techloop string
  wav_play(techloop);                             // Pass to wav player
 
  wav_volume(6);                                  // Adjust volume
  pause(3500);                                    // Play for 3.5 s
  wav_volume(4);                                  // Repeat twice more
  pause(2000);
  wav_volume(8);
  pause(3500);

  wav_stop();                                      // Stop playing
}