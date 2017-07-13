/*
  This uses the OpenWeatherMap's API to form a GET request
  that requests weather by zip code.  See 
  https://openweathermap.org/current#zip for more info.
  
  You will need to create a free accountand and get an 
  API key.  That key becomes part of the GET request.
  
  Important: Your Wi-Fi module has to be connected to a
  Wi-Fi network that allows it Internet access for this 
  to work.  
    
  Application circuit:
  None.
  
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
char str[1024];
char wifi_event;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);
  wifi_setBuffer(str, sizeof(str));

  int tcpHandle = wifi_connect("api.openweathermap.org", 80);
  
  print("tcpHandle = %d\r", tcpHandle);
  
  pause(2000);
  
  // IMPORTANT: Replace YourKeyYourKey... with the API key you 
  // obtain from openweathermap.com when you create a free 
  // account. 

  char request[] = 
  "GET /data/2.5/weather?zip=95677,us"\
  "&appid=YourKeyYourKeyYourKeyYourKeyYour"\
  " HTTP/1.1\r\n"\
  "Host: api.openweathermap.org\r\n"\
  "Connection: keep-alive\r\n"\
  "Accept: *" "/" "*\r\n\r\n";

  int size = strlen(request);
  
  print("GET req size: %d\r", size);
  
  pause(2000);

  wifi_print(TCP, tcpHandle, "%s", request);
  event = wifi_event;
  
  pause(2000);
  size = strlen(str);
  print("size = %d", size);
  
  pause(2000);
  wifi_scan(TCP, tcpHandle, "%s", str); 
  for(int n = 0; n < sizeof(str); n++)
  {
    if(str[n] <= 'z' && str[n] >= ' ')
    {
      print("%c", str[n]);
    }      
    else if(str[n] == 0)
    {
      print("[%d]", str[n]);
      break;
    }      
    else if(str[n] == '\n')
    {
      print("\r", str[n]);
    }      
    else
    {
      print("[%d]", str[n]);
    }      
  }
  char *loc = strstr(str, "temp");
  print("\rloc = %d\r", loc);
  float temp = 0;
  sscan(loc+5, "%f", &temp);
  float degC = temp -273.15;
  print("temp = %6.2f deg C\r", degC); 
  float degF = degC * 9.0 / 5.0 + 32.0;
  print("temp = %6.2f deg C\r", degF); 
}
