/*
  RFID Read.c
  
  Reads and displays RFID tag numbers.
  
  Connect: Vcc to 5V, /ENABLE to P2, SOUT to (R = 2.2 k) to P1, GND to GND
  
  http://www.parallax.com/product/28140
*/

#include "simpletools.h"                      // Include simpletools
#include "rfidser.h"                          // Include rfidser

int rfidEn = 2;                               // Reader /ENABLE pin to P2
int rfidSout = 1;                             // Reader SOUT pin to P1

rfidser *rfid;                                // Set up device ID

int main()                                    // Main function
{
  rfid = rfid_open(rfidSout, rfidEn);         // Open reader, start reading

  while(1)                                    // Main loop
  {
    char *str = rfid_get(rfid, 1000);         // Wait up to 1 s for card
    print("id = %s.\n", str);                 // Print ID.
  }  
}
