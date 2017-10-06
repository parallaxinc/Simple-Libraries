/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int left;
int right;



// ------ Main Program ------
int main() {

  print(("Waiting for servo encoder signals..."));
  print("\r");
  print(("Connected!"));
  print("\r");
  left = 0;
  right = 0;
  while(1) {
    drive_getTicks(&left, &right);
    print(("left = "));
    print("%d", left);
    print((", right = "));
    print("%d\r", right);
    pause(1000);
    if (left % 2) {
      high(26);
    }
    else {
      low(26);
    }

    if (right % 2) {
      high(27);
    }
    else {
      low(27);
    }

  }

}
