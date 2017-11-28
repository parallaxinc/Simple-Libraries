// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int left;
int right;



// ------ Main Program ------
int main() {

  left = 0;
  right = 0;
  while(1) {
    drive_getTicks(&left, &right);
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
