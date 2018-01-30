// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"

// ------ Global Variables and Objects ------
int lightLeft;
int lightRight;
int numerator;
int denominator;
int nDiff;
int speedLeft;
int speedRight;



// ------ Main Program ------
int main() {

  // Light Roaming
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  //
  while(1) {
    // Read light sensors
    high(9);
    pause(1);
    lightLeft = (rc_time(9, 1));
    high(5);
    pause(1);
    lightRight = (rc_time(5, 1));
    //
    // calculate nDiff
    numerator = (200 * lightRight);
    denominator = (lightRight + lightLeft);
    nDiff = (numerator / denominator);
    nDiff = (nDiff - 100);
    nDiff = (nDiff * 4);
    //
    // calculate wheel speeds
    speedLeft = 64;
    speedRight = 64;
    if (nDiff > 0) {
      speedLeft = (64 - nDiff);
    }
    else {
      speedRight = (64 + nDiff);
    }

    drive_speed(speedLeft, speedRight);
  }

}
