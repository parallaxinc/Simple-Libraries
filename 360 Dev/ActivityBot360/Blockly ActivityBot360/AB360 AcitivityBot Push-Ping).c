// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"
#include "ping.h"

// ------ Global Variables and Objects ------
int setPoint;
int kp;
int distance;
int errorVal;
int speed;



// ------ Main Program ------
int main() {

  // AcitivtyBot Push Ping)))
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  drive_setMaxVelocity(FOR_SPEED, 96);
  setPoint = 32;
  kp = -10;
  while(1) {
    distance = ping_cm(8);
    errorVal = (setPoint - distance);
    speed = (kp * errorVal);
    drive_speed(speed, speed);
  }

}
