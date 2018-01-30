// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {

  // Drive Speeds
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  for (int __n = 0; __n < 4; __n++) {
    drive_speed(128, 128);
    pause(2000);
    drive_speed(128, -128);
    pause(200);
    drive_speed(0, 0);
  }

}
