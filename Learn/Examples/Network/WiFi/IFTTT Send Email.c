/*
  Once you have configured your ifttt.com account and created 
  an applet that triggers an email based ona Maker Event, this
  program sends the post request that triggers the email.

  Important: Your Wi-Fi module has to be connected to a
  Wi-Fi network that allows it Internet access for this 
  to work.  
    
  Application circuit:
  None.
    
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  This application makes a post to the If This Then That site
  ifttt.com, which triggers an email to be sent.
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int getFromPageId;
int val;
char str[512];
char wifi_event;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);
  wifi_setBuffer(str, sizeof(str));
  
  int tcpHandle = wifi_connect("maker.ifttt.com", 80);
                                                                                
  char request[] = 
  "POST /trigger/MicrocontrollerEvent/with/key/"\
  "YourKeyYourKeyYourKeyYourKeyYourKeyYourKeyY"\
  " HTTP/1.1\r\n"\
  "Host: maker.ifttt.com\r\n"\
  "Connection: keep-alive\r\n"\
  "Accept: *" "/" "*\r\n\r\n";

  int size = strlen(request);

  wifi_print(TCP, tcpHandle, "%s", request);
  event = wifi_event;
  
  pause(1000);

  wifi_scan(TCP, tcpHandle, "%s", str); 
  
  print("str = %s\r", str); 
}
