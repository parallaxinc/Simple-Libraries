/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "fdserial.h"

// ------ Global Variables and Objects ------
int item;
fdserial *fdser17_16;



// ------ Main Program ------
int main() {
  fdser17_16 = fdserial_open(17, 16, 0b0000, 9600);
  pause(3000);
  while (1) {
    dscan(fdser17_16, "%d", &item);
    print("%s%d\r", "item = ", item);
    pause(500);
  }

}