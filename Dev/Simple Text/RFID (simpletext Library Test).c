/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "rfidser.h"

// ------ Global Variables and Objects ------
rfidser *rfid;
char *rfidBfr;
int ID;



// ------ Main Program ------
int main() {
  rfid = rfid_open(1,2);
  rfid_enable(rfid);while(1) {
    rfidBfr = rfid_get(rfid, 500);
    	sscan(&rfidBfr[2], "%x", &ID);
    	if(ID == 237) ID = 0;print("%s%d\r", "Tag ID: ", ID);
    pause(1000);
  }

}
