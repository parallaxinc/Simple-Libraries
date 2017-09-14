/*
  Application circuit:
  http://learn.parallax.com/tutorials/language/propeller-c/
  propeller-c-simple-circuits/check-pushbuttons  

  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/page-displays-buttons.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int buttonId;
int buttonP3, buttonP4;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  buttonId = wifi_listen(HTTP, "/btns");
  print("getFromPageId = %d\n", buttonId);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    if(event == 'G')
    {
      if(id == buttonId)
      {
        buttonP4 = input(4);
        buttonP3 = input(3);
        wifi_print(GET, handle, "%d%d\r", buttonP4, buttonP3);
        print("Incoming GET request, sending %d%d\r", buttonP4, buttonP3);
      }        
    }
    pause(500);
  }    
}
