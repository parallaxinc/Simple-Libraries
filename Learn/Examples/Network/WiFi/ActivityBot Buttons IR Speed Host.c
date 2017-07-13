/*
  Mechanical Assembly
  http://learn.parallax.com/tutorials/robot/activitybot/
  activitybot/mechanical-assembly

  Electrical Connections
  http://learn.parallax.com/tutorials/robot/activitybot/
  activitybot/electrical-connections
  
  Application Circuit
  http://learn.parallax.com/tutorials/robot/activitybot/activitybot/
  navigate-infrared-flashlights/build-ir-sensor-circuits

  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to match
  the COM control circuit you choose.
  
  Application page should be loaded into the Wi-Fi module
  and then accessed through: 
  http://wi-fi-module's-ip/files/activitybot-btns-ir-speed.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"
#include "abdrive.h"

int event, id, handle;
int navId, spdId, irId;
char buttonCmd, buttonCmdPrev;
int speedLeft = 0, speedRight = 0, speedVal = 50;
int irLeft, irRight;

int main()
{  
  wifi_start(31, 30, 115200, WX_ALL_COM);     

  navId = wifi_listen(HTTP, "/bot"); 
  print("navId: %d\r", navId);
  
  spdId = wifi_listen(HTTP, "/spd");
  print("spdId: %d\r", spdId);
  
  irId = wifi_listen(HTTP, "/ir");
  print("irId: %d\r", irId);

  drive_speed(0, 0);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event: %c, id: %d, handle: %d\r", 
               event,     id,     handle);
    
    if(event == 'P')
    {
      print("Incoming POST request\r");
      if(id == navId)
      {
        wifi_scan(POST, handle, "go%c", &buttonCmd);
        print("go=%c\r", buttonCmd);
        buttonCmdPrev = buttonCmd;
      }
      else if(id == spdId)
      {
        wifi_scan(POST, handle, "v%d", &speedVal);
        print("v=%d\r", speedVal);
        buttonCmd = buttonCmdPrev;
      }
    }
    else if(event == 'G')
    {
      print("Incoming GET request\r");
      
      if(id == irId)
      {
        freqout(11, 1, 38000);
        irLeft = input(10);
    
        freqout(1, 1, 38000);
        irRight = input(2);
    
        print("Reply: %01b%01b\r", irLeft, irRight);
        wifi_print(GET, handle, "%01b%01b\r", irRight, irLeft);
      }        
    }
  
    if(buttonCmd != 0)
    {
      switch(buttonCmd)
      {
        case 'F': 
          speedLeft  =  speedVal;
          speedRight =  speedVal;
          break;
        case 'L':
          speedLeft  = -speedVal;
          speedRight =  speedVal;
          break;
        case 'R':
          speedLeft  =  speedVal;
          speedRight = -speedVal;
          break;
        case 'B':
          speedLeft  = -speedVal;
          speedRight = -speedVal;
          break;
        case 'S':
          speedLeft = 0;
          speedRight = 0;
          break;
      } 
      print("speedLeft: %d, speedRight: %d\r", speedLeft, speedRight);
      drive_speed(speedLeft, speedRight);
      buttonCmd = 0;
    }            
    pause(200);
  }    
}
