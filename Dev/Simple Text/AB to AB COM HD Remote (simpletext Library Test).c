// ------ Libraries and Definitions ------
#include "simpletools.h"
//#include "fdserial.h"

// ------ Global Variables and Objects ------
int item;
int val;
serial *ser17_16;

// ------ Main Program ------
int main() {
  ser17_16 = serial_open(17, 16, 0b0000, 9600);
  val = 0;
  while (1) {
    val = (val + 1);
    dprint(ser17_16, "%d\r", val);
    pause(1000);
  }

  item = (item + 1);
}