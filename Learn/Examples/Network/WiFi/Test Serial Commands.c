/*
  Application circuit:
  Any if you leave the More Network Tests section commented.
  If you un-comment it, use:
    DO -> P9, DI <- P8, SEL - GND.  Use USB cable and the 
    USB COM port for loading code and debugging. 
  
  Note: This example relies on the 0.8 version of the wifi library.  
  Updates may change some function behaviors in later releases.
*/

#include "simpletools.h"
#include "wifi.h"

char status;
char s[64];
int pinState = 0;

int main()
{
  wifi_start(31, 30, 115200, WX_ALL_COM);
  //wifi_start(9, 8, 115200, USB_PGM_TERM);

  print("=======================================\r");
  print("wifi_print/scan tests\r");
  print("=======================================\r\r");

  // TEST I/O CONTROL WITH wifi_print/scan //
  print("Test controlling Wi-Fi module I/O\r");
  print("Set /CTS ouput-high\r");
  wifi_print(CMD, NULL, "%cSET:pin-gpio%d,%d\r", CMD, GPIO_CTS, 1);
  wifi_scan(CMD, NULL, "%c", &status);
  print("status: %c\r", status);

  print("Check /CTS\r");
  wifi_print(CMD, NULL, "%cCHECK:pin-gpio%d\r", CMD, GPIO_CTS);
  wifi_scan(CMD, NULL, "%c%d", &status, &pinState);
  print("status: %c, pinState: %d\r", status, pinState);

  print("Set /CTS ouput-low\r");
  wifi_print(CMD, NULL, "%cSET:pin-gpio%d,%d\r", 
                     CMD, GPIO_CTS, 0);
  wifi_scan(CMD, NULL, "%c", &status);
  print("status: %c\r", status);

  print("Check /CTS\r");
  wifi_print(CMD, NULL, "%cCHECK:pin-gpio%d\r", CMD, GPIO_CTS);
  wifi_scan(CMD, NULL, "%c%d", &status, &pinState);
  print("status: %c, pinState: %d\r", status, pinState);
                  
  print("Check /CTS for pull-up when \rinput should return high\r");
  wifi_print(CMD, NULL, "%cCHECK:pin-gpio%d\r", CMD, GPIO_CTS);
  wifi_scan(CMD, NULL, "%c%d", &status, &pinState);
  print("status: %c, pinState: %d\r\r", status, pinState);
  
  // Check IP Address
  print("Check station IP address\r");
  int ip[4] = {0, 0, 0, 0};
  wifi_print(CMD, NULL, "%cCHECK:station-ipaddr\r", CMD);
  wifi_scan(CMD, NULL, "%c%d%d%d%d", &status, &ip[0], &ip[1], &ip[2], &ip[3]);
  print("Station IP: %d.%d.%d.%d\r\r", ip[0], ip[1], ip[2], ip[3]);
  
  // Check Firmwre Version //
  //"\xfe=S,v1.0 (2016-11-02 18:04:30)\r";
  char temp[64];
  memset(temp, 0, 64);
  float version = 0.0;
  print("Check firmware version\r");
  wifi_print(CMD, NULL, "%cCHECK:version\r", CMD);
  wifi_scan(CMD, NULL, "%2s%f", s, &version);
  print("Truncated reply: %4.2f\r", version);
  int charcount = wifi_replyStringCopy(temp);
  print("charcount: %d\rfull reply: %s\r", charcount, temp);
  

  print("=======================================\r");
  print("wifi_command tests\r");
  print("=======================================\r\r");


  // Test I/O control
  char *reply;
  print("Test controlling Wi-Fi module I/O\r");
  print("Set /CTS ouput-high\r");
  reply = wifi_command("SET:pin-gpio13,1\r");
  print("reply: %s", reply);

  print("Check /CTS\r");
  reply = wifi_command("CHECK:pin-gpio13\r");
  print("reply: %s", reply);

  print("Set /CTS ouput-low\r");
  reply = wifi_command("SET:pin-gpio13,0\r");
  print("reply: %s", reply);

  print("Check /CTS\r");
  reply = wifi_command("CHECK:pin-gpio13\r");
  print("reply: %s", reply);
                  
  print("Check /CTS for pull-up when \rinput should return high\r");
  reply = wifi_command("CHECK:pin-gpio13\r");
  print("reply: %s\r", reply);
  
  
  // Check Firmwre Version //
  //"\xfe=S,v1.0 (2016-11-02 18:04:30)\r";
  print("Check firmware version\r");
  reply = wifi_command("CHECK:version\r");
  print("reply: %s\r", reply);
  
  // Check Module Name //
  print("Check module name\r");
  wifi_print(CMD, NULL, "%cCHECK:module-name\r", CMD);
  wifi_scan(CMD, NULL, "%1s%s", s, s);
  print("Module name: %s\r\r", &s[1]);


  // Check network mode
  print("Check network mode\r");
  reply = wifi_command("CHECK:wifi-mode\r");
  print("reply: %s\r", reply);


  // Check network mode
  print("Check network mode\r");
  reply = wifi_command("CHECK:wifi-mode\r");
  print("reply: %s\r", reply);
  
  // Check IP Address //
  print("Check station IP address\r");
  reply = wifi_command("CHECK:station-ipaddr\r");
  print("reply: %s\r", reply);
  /* 
  

  print("=======================================\r");
  print("More Network Command Tests\r");
  print("=======================================\r\r");



  // Disconnect from a network
  print("Disconnect from the host network\r");
  reply = wifi_command("SET:wifi-mode,AP\r");
  print("reply: %s\r", reply);

  //pause(5000);

  // Check network mode
  print("Check network mode\r");
  reply = wifi_command("CHECK:wifi-mode\r");
  print("reply: %s\r", reply);

  //pause(5000);

  // Set Mode to Station + AP //
  //
  print("Set mode to STA+AP\r");
  reply = wifi_command("SET:wifi-mode,STA+AP\r");
  print("reply: %s\r", reply);

  //pause(5000);

  // Check network mode //
  print("Check network mode\r");
  reply = wifi_command("CHECK:wifi-mode\r");
  print("reply: %s\r", reply);
  //

  //pause(5000);


  // Join a network //
  //
  print("Join a Network\r");
  reply = wifi_command("JOIN:"WiFiApSSID", "passphrase"\r");
  print("reply: %s\r", reply);
  
  pause(5000);
  
  //wifi_stop();
  //wifi_start(31, 30, 115200, WX_ALL_COM);

  //pause(5000);

  // Check IP Address //
  print("Check station IP address\r");
  reply = wifi_command("CHECK:station-ipaddr\r");
  print("reply: %s\r", reply);

  //pause(5000);

  // Set Mode to Station + AP //
  print("Set mode to STA\r");
  reply = wifi_command("SET:wifi-mode,STA\r");
  print("reply: %s\r", reply);

  //pause(5000);

  // Check network mode
  print("Check network mode\r");
  reply = wifi_command("CHECK:wifi-mode\r");
  print("reply: %s\r", reply);

  //pause(5000);
  print("Check station ip\r");
  int ipaddr[] = {0, 0, 0, 0};
  status = wifi_ip(STA, ipaddr);
  print("ip=%d.%d.%d.%d\r", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);
  
  */
  
}

