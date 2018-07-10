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
char getReplyContent[512];
char getReplyHeader[356];

int wifi_termShowStrAndNPCs(char *s);

int wifi_getNamedValue(char *strSource, char *strName, char *fmt, ...);

int main()
{
  //wifi_start(31, 30, 115200, WX_ALL_COM);
  wifi_start(9, 8, 115200, USB_PGM_TERM);
  wifi_setBuffer(str, sizeof(str));
  
  print("Waiting 10 s...");
  pause(10000);
  print("done!\r\r");
  
  while(1)
  {
    memset(str, 0, sizeof(str));

    int tcpHandle = wifi_connect("api.openweathermap.org", 80);
    
    pause(2000);
    
    print("tcpHandle: %d\r", tcpHandle);
    
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
    
    int length = strlen(request);
    
    print("GET request length: %d\r", length);
    print("GET request\r======================================\r");
    wifi_termShowStrAndNPCs(request);
    print("\r------------------------------------\rEnd of GET request\r\r\r");
    
    pause(2000);
  
    wifi_print(TCP, tcpHandle, "%s", request);
    
    pause(2000);
    print("WX serial response: %s\r\r", str);
    
    pause(2000);
    wifi_scan(TCP, tcpHandle, "%s", str); 
    
    length = strlen(str);
    print("Server response length: %d\r", length); 
    print("Server response to GET request\r");
    print("======================================\r");
    wifi_termShowStrAndNPCs(str);
    print("\r------------------------------------\r");
    print( "End of server response to GET request\r\r");
    
    float temp = 0;
    wifi_getNamedValue(str, "temp", "%f", &temp);
    print("temp = %6.2f deg K\r", temp);

    wifi_disconnect(tcpHandle);
    float degC = temp -273.15;
    print("temp = %6.2f deg C\r", degC); 
    float degF = degC * 9.0 / 5.0 + 32.0;
    print("temp = %6.2f deg C\r", degF); 
    
    print("\rdelay...");
    pause(20000);
    print("done!\r\r\r");
  }    
}


int wifi_termShowStrAndNPCs(char *s)
{
  int size = strlen(s);
  for(int n = 0; n <= size; n++)
  {
    if(s[n] <= 'z' && s[n] >= ' ')
    {
      print("%c", s[n]);
    }      
    else if(s[n] == 0)
    {
      print("[%d]", s[n]);
      break;
    }  
    else if(s[n] == '\n' || s[n] == '\r')
    {
      print("[%d]%c", s[n], s[n]);
    }      
    else
    {
      print("[%d]", s[n]);
    }   
    //pause(10);   
  }
  pause(10);
  return size;
}  


int wifi_getNamedValue(char *strSource, char *strName, char *fmt, ...)
{
  char *loc = strstr(strSource, strName);
  loc += strlen(strName);
  va_list args;
  va_start(args, fmt);
  int n = _doscanf(loc, fmt, args);
  va_end(args);
  return n;
}  


