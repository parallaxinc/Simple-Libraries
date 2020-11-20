/*
  Application circuit:
  http://learn.parallax.com/tutorials/language/propeller-c/
  propeller-c-simple-devices/standard-servo  

  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/page-controls-servo.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "servo.h"
#include "wifi.h"

int event, id, handle;
int servoId, angle;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);
  servoId = wifi_listen(HTTP, "/servo");
  print("ledId = %d\n", servoId);
  
  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    
    if(event == 'P')
    {
      if(id == servoId)
      {
        print("Incoming POST request\r");
        wifi_scan(POST, handle, "angle%d\r", &angle);
        print("servoAngle: %d\n", angle);
        servo_angle(16, angle * 10);
      }        
    }
    pause(500);
  }    
}
