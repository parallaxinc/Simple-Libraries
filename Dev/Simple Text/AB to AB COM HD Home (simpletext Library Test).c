/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
//#include "fdserial.h"

// ------ Global Variables and Objects ------
int item;
serial *ser16_17;

// ------ Main Program ------
int main() {
  ser16_17 = serial_open(16, 17, 0b0000, 9600);
  while (1) {
    dscan(ser16_17, "%d", &item);
    print("%s%d\r", "item = ", item);
    pause(250);
  }

}