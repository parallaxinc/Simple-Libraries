/*
  Prop to Prop via WX Verbose (Host).c
  
  Responds to GET requests from client with x=X, y=Y where X is incremented with
  each response, and Y=2X.
  
  NOTE: This is very similar to the propeller C code from:
  http://learn.parallax.com/tutorials/language/propeller-c/parallax-wx-wi-fi-module-prop-c/page-requests-info-propeller
*/

#include "simpletools.h"
#include "wifi.h"

int event, id, handle;
int getFromPageId;
int x = 0, y = 0;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);

  getFromPageId = wifi_listen(HTTP, "/tpfm");
  print("getFromPageId = %d\n", getFromPageId);

  while(1)
  {
    wifi_poll(&event, &id, &handle); 
    print("event = %c, id = %d, handle = %d\r", event, id, handle);
    if(event == 'G')
    {
      if(id == getFromPageId)
      {
        x++;
        y = 2 * x;
        print("Host: x=%d, y=%d\r", x, y);
        wifi_print(GET, handle, "x=%d, y=%d\r", x, y);
      }        
    }
    pause(120);
  }    
}
