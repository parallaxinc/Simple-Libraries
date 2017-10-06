// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int left;
int right;
int leftPrev;
int rightPrev;



// ------ Main Program ------
int main() {

  left = 0;
  right = 0;
  leftPrev = 0;
  rightPrev = 0;
  while(1) {
    drive_getTicks(&left, &right);
    if (left != leftPrev) {
      toggle(26);
      	set_direction(26, 1);
    }

    if (right != rightPrev) {
      toggle(27);
      	set_direction(27, 1);
    }

    leftPrev = left;
    rightPrev = right;
  }

}
