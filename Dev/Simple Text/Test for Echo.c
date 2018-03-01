/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"

// ------ Global Variables and Objects ------
int item;



// ------ Main Program ------
int main() {

  item = 0;
  pause(2500);
  while (1) {
    print("Enter a number: ");
    scan("%d\n", &item);
    print("%s%d\r", "You entered: ", item);
  }

}