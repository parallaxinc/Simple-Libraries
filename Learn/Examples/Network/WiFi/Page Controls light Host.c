/*
  Application circuit:
  http://learn.parallax.com/tutorials/language/propeller-c/
  propeller-c-simple-circuits/blink-light  

  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/page-controls-light.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int ledId, pin, state;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);
  ledId = wifi_listen(HTTP, "/leds");
  print("ledId = %d\n", ledId);
  
  set_direction(26, 1);
  set_direction(27, 1);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    if(event == 'P')
    {
      if(id == ledId)
      {
        print("Incoming POST request\r");
        wifi_scan(POST, handle, "io%d%d", &pin, &state);
        print("pin=%d, state=%d\n", pin, state);
        set_output(pin, state);
      }        
    }
    pause(500);
  }    
}
