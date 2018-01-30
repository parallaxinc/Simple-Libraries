// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {

  // AB360 ActivityBot Taking Turns
  freqout(4, 1000, 3000);
  // Rotate
  drive_speed(64, -64);
  pause(2000);
  drive_speed(0, 0);
  freqout(4, 1000, 2500);
  // Rotate
  drive_speed(64, -32);
  pause(2000);
  drive_speed(0, 0);
  freqout(4, 1000, 2000);
  // Tight arc
  drive_speed(64, 0);
  pause(2000);
  drive_speed(0, 0);
  freqout(4, 1000, 1500);
  // Wide arc
  drive_speed(64, 32);
  pause(2000);
  drive_speed(0, 0);

}
