// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int left_whisker;
int right_whisker;



// ------ Main Program ------
int main() {
  ee_getInt(32768); // NOTE: This is a temporary patch to make the AB360 robot library compile correctly.
  // Whisker Roaming
  freqout(4, 1000, 3000);
  while(1) {
    left_whisker = input(7);
    right_whisker = input(8);
    if (left_whisker == 0  || right_whisker == 0) {
      drive_speed(-64, -64);
    }
    else {
      drive_speed(0, 0);
    }

  }

}
