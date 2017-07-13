/*
  Application circuit:
  DO -> P11, DI <- P10, SEL - GND.  Use USB cable and the 
  USB COM port for loading code and debugging. 
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int main()
{
  wifi_start(9, 8, 115200, USB_PGM_TERM);

  print("Leave a Network\r");
  
  // Leaves network where it was a station and sets 
  // the Wi-Fi module's mode.  This example puts the 
  // Wi-Fi module in AP (access point) mode after 
  // leaving the network.  Another option is STA_AP,
  // which would make the Wi-Fi module ready to join 
  // another network.

  wifi_leave(AP);

  // Verify mode after leaving the network.

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
