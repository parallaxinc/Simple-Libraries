/*
  Application circuit:
  None.
    
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/val-from-micro.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int getFromPageId;
int val;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  getFromPageId = wifi_listen(HTTP, "/tpfm");
  print("getFromPageId = %d\n", getFromPageId);

  while(1)
  {
    val++;
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    if(event == 'G')
    {
      if(id == getFromPageId)
      {
        print("Incoming GET request, sending %d\r", val);
        wifi_print(GET, handle, "%d", val);
      }        
    }
    pause(500);
  }    
}
