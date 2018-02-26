/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "fdserial.h"

// ------ Global Variables and Objects ------
int item;
fdserial *fdser9_8;



// ------ Main Program ------
int main() {
  fdser9_8 = fdserial_open(9, 8, 0b0000, 9600);
  while (1) {
    dscan(fdser9_8, "%d", &item);
    print("%s%d\r", "item = ", item);
    pause(500);
  }

}