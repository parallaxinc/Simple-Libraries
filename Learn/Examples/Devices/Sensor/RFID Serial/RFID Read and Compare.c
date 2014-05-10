/*
  RFID Read and Compare.c
  
  After scanning your ID cards, you can copy their ID strings over the ones
  in the else if statements in this program to recognize them.
  
  Connect: Vcc to 5V, /ENABLE to P2, SOUT to (R = 2.2 k) to P1, GND to GND
  
  http://www.parallax.com/product/28140
*/

#include "simpletools.h"                      // Include simpletools
#include "rfidser.h"                          // Include rfidser

int rfidEn = 2;                               // Reader /ENABLE pin
int rfidSout = 1;                             // Reader SOUT pin

rfidser *rfid;                                // Set up device ID

int main()                                    // Main function
{
  rfid = rfid_open(rfidSout, rfidEn);         // Open reader, start reading

  while(1)                                    // Main loop
  {
    char *str = rfid_get(rfid, 1000);         // Wait up to 1 s for card

    if(!strcmp(str, "timed out"))             // Timed out?
      print("No ID scanned.\n");              //   display "No ID..."
    else if(!strcmp(str, "70006E0299"))       // Round card ID match?
      print("Round card.\n");                 //   display "Round..."
    else if(!strcmp(str, "0200822A14"))       // Rectangle card ID match?
      print("Rectangle card.\n");             //   display "Rectangle..."
    else                                      // No matches?
      print("id = %s.\n", str);               //   print ID.
  }  
}
