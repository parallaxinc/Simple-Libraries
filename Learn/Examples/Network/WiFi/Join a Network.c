/*
  Join a Network.c
  
  Make sure to update the SSID and passphrase parameters in the
  wifi_join call before running.  

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

  print("Join a network:\r");
  wifi_join("SSID", "passphrase");

  int ip[] = {0, 0, 0, 0};
  memset(ip, 0, 16);
  do
  {
    wifi_ip(STA, ip);
  }while(ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0);
  print("\rip=%d.%d.%d.%d\r", ip[0], ip[1], ip[2], ip[3]);
    
  int mode = wifi_mode(CHECK);
  switch(mode)
  {
    case STA:    //0xf4: 
      print("mode=STA\r");
      break;
    case AP:     //0xf3  
      print("mode=AP\r");
      break;
    case STA_AP: //0xf2
      print("mode=STA+AP");
      break;
  }     
}
