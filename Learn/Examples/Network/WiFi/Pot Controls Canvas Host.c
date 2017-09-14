/*
  Application circuit:
  http://learn.parallax.com/tutorials/language/propeller-c/
  propeller-c-simple-circuits/measure-volts
  (Don't worry about the A/D2 connection, just A/D3.
  
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/pot-controls-canvas.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"
#include "abvolts.h"

int event, id, handle;
int dialId;
int dialAngle;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  dialId = wifi_listen(HTTP, "/dial");
  print("dialId = %d\n", dialId);
  
  ad_init(21, 20, 19, 18);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event: %c, id: %d, handle: %d\r", 
               event,     id,     handle);
               
    if(event == 'G')
    {
      if(id == dialId)
      {
        dialAngle  = ad_in(3);
        dialAngle *= 270;
        dialAngle /= 2703;
        
        print("Incoming GET request, sending %d\r", dialAngle);
        wifi_print(GET, handle, "%d", dialAngle);
      }        
    }
    pause(500);
  }    
}
