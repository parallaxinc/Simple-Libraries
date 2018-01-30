// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int irLeft;
int irRight;



// ------ Main Program ------
int main() {

  // IR Roaming
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  low(26);
  low(27);
  while(1) {
    freqout(11, 1, 38000);
    irLeft = input(10);
    freqout(1, 1, 38000);
    irRight = input(2);
    if (irLeft == 1  && irRight == 1) {
      drive_speed(64, 64);
    }
    else if (irLeft == 0  && irRight == 0) {
      drive_speed(-64, -64);
    }else if (irLeft == 0) {
      drive_speed(64, -64);
    }else if (irRight == 0) {
      drive_speed(-64, 64);
    }
  }

}
