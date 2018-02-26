/*
  Application circuit:
  None.
    
  Important: Your Wi-Fi module has to be connected to a
  Wi-Fi network that allows it Internet access for this 
  to work.  
    
  Programming and Wi-Fi selection circuits at:
  http://learn.parallax.com/propeller-c-wx-wi-fi 
  Make sure to change the wifi_start call in the code to 
  match the COM control circuit you choose.
  
  This application does not make the Wi-Fi module serve
  and monitor a page.  Instead, it grabs text from this
  page on the Internet: 
    www-eng-x.llnl.gov//documents/a_document.txt
  
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

  int tcpHandle = wifi_connect("www-eng-x.llnl.gov", 80);

  char request[] = "GET /documents/a_document.txt "\
                   "HTTP/1.1\r\n"\
                   "Host: www-eng-x.llnl.gov\r\n\r\n\0";

  int size = strlen(request);

  wifi_print(TCP, tcpHandle, "%s", request);
  event = wifi_event;
  
  pause(1000);

  wifi_scan(TCP, tcpHandle, "%s", str); 
  
  print("str = %s\r", str); 
}
