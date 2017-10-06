// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {
  servo360_connect(0,0);

  // Drive Speeds Try This
  freqout(4, 1000, 3000);
  for (int __n = 0; __n < 4; __n++) {
    drive_speed(64, 64);
    pause(2000);
    drive_speed(64, -64);
    pause(350);
    drive_speed(0, 0);
  }

}
