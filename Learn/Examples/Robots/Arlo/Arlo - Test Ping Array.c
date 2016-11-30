/*
  Arlo - Test Ping Array.c
*/

#include "simpletools.h"
#include "ping.h"

int n = 0, pingPin, cmDist;
int pins[4] = {14, 16, 17, 15};

int main()
{
  while(1)
  {
    if(n == 0)
    {
      print("%c", HOME);
      print("Ping))) Distances\n");
      print("-----------------\n");
    }
    
    pingPin = pins[n];
    cmDist = ping_cm(pingPin);
    
    switch(pingPin)
    {
      case 14: print("Front: "); break;
      case 16: print("Left:  "); break;
      case 17: print("Right: "); break;
      case 15: print("Back:  "); break;
    }
    
    print("%03d cm\n", cmDist);
    n++;
    if(n >= 4) n =0;
    pause(200);
  }    
}