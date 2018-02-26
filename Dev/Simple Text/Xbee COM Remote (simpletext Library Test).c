// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "fdserial.h"

// ------ Global Variables and Objects ------
int val;
fdserial *fdser9_8;



// ------ Main Program ------
int main() {
  fdser9_8 = fdserial_open(9, 8, 0b0000, 9600);
  val = 0;
  while (1) {
    val = (val + 1);
    dprint(fdser9_8, "%d\r", val);
    pause(1000);
  }

}