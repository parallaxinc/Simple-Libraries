/*
  Prop to Prop via WX Verbose (Client).c
  
  Sends TCP GET request to host, and displays values in responses. 
  
  NOTE: The TCP message this page sends is very similar to what the browser sends in response to 
        an update button click in:
  http://learn.parallax.com/tutorials/language/propeller-c/parallax-wx-wi-fi-module-prop-c/page-requests-info-propeller
*/

#include "simpletools.h"                     // Library includes
#include "wifi.h"

// IMPORTANT: Use the IP address for your host WX in both the hostIP 
//            and request strings.

char hostIP[] = "192.168.43.243";            // Host IP address
char request[] =                             // TCP GET request
"GET /tpfm HTTP/1.1\r\n"\                
"Host: 192.168.43.243\r\n"\
"Connection: keep-alive\r\n"\
"Accept: *" "/" "*\r\n\r\n";

int tcpHandle = 0;                            // Connection handle
int event, id, handle;                        // wifi_poll variables
char tcp_str[256];                            // TCP string
int x = 0, y = 0;                             // Test values

int main()                                    // Main function
{
  wifi_start(31, 30, 115200, WX_ALL_COM);     // Start wifi in other processor
  wifi_setBuffer(tcp_str, sizeof(tcp_str));   // Use tcp_str instead of default
  
  while(1)                                    // Main loop
  {
    print("Connection attempts: ");
    tcpHandle = 0;                            // Connection handle
    int n = 1;                                // Connection attempts
    while(tcpHandle < 5)
    {
      print("%d, ", n++);
      tcpHandle = wifi_connect(hostIP, 80);   // Try to open connection
    }            
    print("\r");
    print("tcpHandle = %d\r\r", tcpHandle);
    
    int length = strlen(request);
    print("GET request length: %d\r", length);
    print("GET request\r======================================\r");
    putStrWithNpcVals(request);
    print("\r------------------------------------\rEnd of GET request\r\r\r");
    pause(20);
    
    // Send TCP request via connection handle
    wifi_print(TCP, tcpHandle, "%s", request); 
            
    for(int n = 0; n < 100; n++)              // Poll for response 
    {
      //memset(tcp_str, 0, sizeof(tcp_str));    // Clear TCP string
      wifi_poll(&event, &id, &handle);        // Check event
      print("event: %c, id: %d, handle: %d\r", 
                 event,     id, handle);
      pause(10);
                 
      if(event == 'D')                        // If data received...
      {
        putStrWithNpcVals("\r\rWX serial response: ");
        putStrWithNpcVals(tcp_str);
        pause(20);

        wifi_scan(TCP, tcpHandle,             // Store data in tcp_str 
                  "%s", tcp_str); 

        length = strlen(tcp_str);
        print("\r\r\rServer response length: %d\r", length); 
        print("Server response to GET request\r");
        print("======================================\r");
        putStrWithNpcVals(tcp_str);
        print("\r------------------------------------\r");
        print( "End of server response to GET request\r\r\r");
        pause(20);

        // Get values after x= and y=
        sscanAfterStr(tcp_str, "x=", "%d", &x);
        sscanAfterStr(tcp_str, "y=", "%d", &y);
        
        // Display values
        print("Client: x = %d, y = %d\r", x, y);
        
        // After processing x and y, preak out of the for... loop
        break;
      }
    }               
    
    print("\r\rDisconnect from handle %d\r\r\r...\r\r\r", tcpHandle);
    wifi_disconnect(tcpHandle);               // Disconnect after exhcange

    // IMPORTANT: Frequency of requests should be less than max response
    //            frequency.  So, make sure to a pause here that's longer
    //            than in host back end code.
    pause(250);
  }    
}



