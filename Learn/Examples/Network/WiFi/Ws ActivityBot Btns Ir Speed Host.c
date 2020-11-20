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
  http://wi-fi-module's-ip/files/ws-activitybot-btns-ir-speed.html
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "abdrive.h"
#include "wifi.h"

int event, id, handle;
int wsId, wsHandle = 0;
int navChar, buttonCmd, buttonCmdPrev; 
int val, speedVal, speedLeft, speedRight;
int irLeft, irRight; 

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  wsId = wifi_listen(WS, "/ws/a");
  print("wsId = %d\n", wsId);
  
  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    //print("event = %c, id = %d, handle = %d\r", event, id, handle);

    if(event == 'W')
    {
      if(id == wsId)
      {
        wsHandle = handle;
        print("wsHandle = %d\n\n", wsHandle);
      }        
    }
    else if(event == 'D')
    {
      //print("Incoming websocket data\r");
      wifi_scan(WS, handle, "%c%d", &buttonCmd, &val);
      //print("direction: %c, speed: %d\n", buttonCmd, val);
      if(buttonCmd == 'v')
      {
        buttonCmd = buttonCmdPrev;
        speedVal = val;
      }        
      else 
      {
        buttonCmdPrev = buttonCmd;
      }        
    }
    if(wsHandle != 0)
    {
      freqout(11, 1, 38000);
      irLeft = input(10);
  
      freqout(1, 1, 38000);
      irRight = input(2);

      wifi_print(WS, wsHandle, "%01b%01b", irLeft, irRight);
    }       

    if(buttonCmd != 0)
    {
      switch(buttonCmd)
      {
        case 'F': 
          speedLeft = speedVal;
          speedRight = speedVal;
          break;
        case 'L':
          speedLeft = -speedVal;
          speedRight = speedVal;
          break;
        case 'R':
          speedLeft = speedVal;
          speedRight = -speedVal;
          break;
        case 'B':
          speedLeft = -speedVal;
          speedRight = -speedVal;
          break;
        case 'S':
          speedLeft = 0;
          speedRight = 0;
          break;
      } 

      //print("speedLeft: %d, speedRight: %d\r", speedLeft, speedRight);
      drive_speed(speedLeft, speedRight);
      buttonCmd = 0;
    }            

    pause(50);
  }    
}
