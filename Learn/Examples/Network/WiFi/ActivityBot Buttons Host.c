/*
  Mechanical Assembly
  http://learn.parallax.com/tutorials/robot/activitybot/
  activitybot/mechanical-assembly

  Electrical Connections
  http://learn.parallax.com/tutorials/robot/activitybot/
  activitybot/electrical-connections
  
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to match
  the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/activitybot-btns.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"
#include "abdrive.h"

int event, id, handle;
int navId;
char buttonCmd;
int speedLeft = 0, speedRight = 0;

int main()
{  
  wifi_start(31, 30, 115200, WX_ALL_COM);     

  navId = wifi_listen(HTTP, "/bot"); 
  print("navId = %d\n", navId);
  
  drive_speed(10, 10);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event: %c, id: %d, handle: %d\r", 
               event,     id,     handle);
    
    if(event == 'P')
    {
      if(id == navId)
      {
        print("Incoming POST request\r");
        pause(500);
        wifi_scan(POST, handle, "go%c", &buttonCmd);
        print("go=%c\n", buttonCmd);
      }        
    }
    
    if(buttonCmd != 0)
    {
      switch(buttonCmd)
      {
        case 'F': 
          if(speedLeft > speedRight) speedRight = speedLeft;
          else if(speedRight > speedLeft) speedLeft = speedRight;
          else
          {
            speedLeft += 16;
            speedRight += 16;
          }            
          break;
        case 'L':
          speedLeft -= 16;
          speedRight += 16;
          break;
        case 'R':
          speedLeft += 16;
          speedRight -= 16;
          break;
        case 'B':
          if(speedLeft < speedRight) speedRight = speedLeft;
          else if(speedRight < speedLeft) speedLeft = speedRight;
          else
          {
            speedLeft -= 16;
            speedRight -= 16;
          }            
          break;
        case 'S':
          speedLeft = 0;
          speedRight = 0;
          break;
      } 
      if(speedLeft  >= 128)  speedLeft  = 128;
      if(speedLeft  <= -128) speedLeft  = -128;
      if(speedRight >= 128)  speedRight = 128;
      if(speedRight <= -128) speedRight = -128;         

      drive_speed(speedLeft, speedRight);
      print("speedLeft = %d, speedRight = %d\r", speedLeft, speedRight);
      buttonCmd = 0;
    }            
    pause(200);
  }    
}
