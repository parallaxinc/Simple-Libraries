/*
  Test WAV Player.c
  Click Help and select Tutorials to see lots of code and 
  application examples. 
  
  You will need two 16-bit 32 ksps mono .wav files on your SD card's
  root directory: levels.wav & crazy.wav.  
*/

#include "simpletools.h"
#include "wavplayer.h"

int main()                                    // Main function
{
  int DO = 22, CLK = 23, DI = 24, CS = 25;    // SD I/O pins
  sd_mount(DO, CLK, DI, CS);                  // Mount SD card
  
  const char levels[] = {"levels.wav"};       // Set up levels string
  wav_play(levels);                           // Pass to wav playwer
  
  wav_volume(7);                              // Adjust volume
  pause(5000);
  wav_volume(3); 
  pause(5000);
  wav_volume(5); 
  pause(5000);

  wav_stop();                                 // Stop playing
  pause(1000);
  
  const char crazy[] = {"crazy.wav"};         // Start playing crazy.wav
  wav_play(crazy);

  while(1);                                   // Keep this cog alive
}