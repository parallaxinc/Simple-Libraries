// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"
#include "ping.h"

// ------ Global Variables and Objects ------
int turn;



// ------ Main Program ------
int main() {
  srand(INA + CNT);

  // Ping))) Detect and Turn Random
  freqout(4, 1000, 3000);
  drive_setAcceleration(FOR_SPEED, 600);
  while(1) {
    while ((ping_cm(8) >= 20)) {
      pause(5);
    }
    turn = ((1 + rand() % (2 - 1 + 1)));
    if (turn == 1) {
      drive_speed(64, -64);
    }
    else {
      drive_speed(-64, 64);
    }

    while ((ping_cm(8) < 20)) {
    }
    drive_speed(0, 0);
  }

}
