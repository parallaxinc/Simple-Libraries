/*
  Check Station IP Address.c
  
  Check the current station IP address.
  
  Application circuit:
  DO -> P9, DI <- P8, SEL - GND.  Use USB cable and the 
  USB COM port for loading code and debugging. 
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int main()
{
  wifi_start(9, 8, 115200, USB_PGM_TERM);
  
  print("Check Station IP Address\r");

  int ip[] = {0, 0, 0, 0};
  memset(ip, 0, 16);
  do
  {
    wifi_ip(STA, ip);
  }
  while(ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0);

  print("\rip=%d.%d.%d.%d\r", ip[0], ip[1], ip[2], ip[3]);
}
