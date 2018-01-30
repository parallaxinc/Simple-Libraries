// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int left_whisker;
int right_whisker;



// ------ Main Program ------
int main() {

  // Whisker Roaming
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  while(1) {
    drive_speed(64, 64);
    left_whisker = input(7);
    right_whisker = input(8);
    if (left_whisker == 0) {
      drive_speed(-64, -64);
      pause(1000);
      drive_speed(64, -64);
      pause(500);
    }
    else if (right_whisker == 0) {
      drive_speed(-64, -64);
      pause(1000);
      drive_speed(-64, 64);
      pause(500);
    }
  }

}
