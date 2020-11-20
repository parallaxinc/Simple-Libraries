/*
  Application circuit:
  None.
    
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/text-page-to-micro.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int postFromPageId;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  postFromPageId = wifi_listen(HTTP, "/fptm");
  print("postFromPageId = %d\n", postFromPageId);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    if(event == 'P')
    {
      if(id == postFromPageId)
      {
        print("Incoming POST request\r");
        char s[6];
        int n = wifi_scan(POST, handle, "txt%s", &s);
        print("text = %s n = %d\n", s, n);
      }        
    }
    pause(500);
  }    
}
