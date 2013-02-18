/*
  Test WAV Player.c
*/

#include "simpletools.h"
#include "ping.h"
#include "wavplayer.h"

int main()                                    // Main function
{
  pause(1000);                                // Wait 1 s for host

  int DO = 22, CLK = 23, DI = 24, CS = 25;
  sd_mount(DO, CLK, DI, CS);
  
  const char levels[] = {"levels.wav"};
  wav_play(levels);

  while(1)
  {
    int dist = ping_cm(9);
    dist = dist / 3;
    if(dist > 10) dist = 10;
    dist = 10 - dist;
    wav_volume(dist);
    pause(100);
  }
}
