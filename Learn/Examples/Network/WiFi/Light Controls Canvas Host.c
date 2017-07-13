/*
  Application circuit:
  http://learn.parallax.com/tutorials/language/propeller-c
  /propeller-c-simple-circuits/sense-light
  
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to match
  the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/light-controls-canvas.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int lightId;
int lightVal;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  lightId = wifi_listen(HTTP, "/light");
  print("getFromPageId = %d\n", lightId);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", 
                event,      id,      handle);

    if(event == 'G')
    {
      if(id == lightId)
      {
        high(5);
        pause(1);
        lightVal = rc_time(5, 1);
        
        wifi_print(GET, handle, "%d\n", lightVal);
        print("Reqply to GET request:%d\n", lightVal);
      }        
    }
    pause(500);
  }    
}
