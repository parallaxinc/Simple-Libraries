// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "fdserial.h"

// ------ Global Variables and Objects ------
int val;
fdserial *fdser16_17;



// ------ Main Program ------
int main() {
  fdser16_17 = fdserial_open(16, 17, 0b0000, 9600);
  val = 0;
  while (1) {
    val = (val + 1);
    dprint(fdser16_17, "%d\r", val);
    pause(1000);
  }

}