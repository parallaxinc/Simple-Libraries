/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"



// ------ Main Program ------
int main() {
  servo360_connect(12,14);

  print(("Hello"));
  servo360_speed(12, 180);
  pause(2000);
  print(("angle = "));
  print("%d\r", (servo360_getAngle(12)));
  servo360_speed(12, -180);
  pause(2000);
  print(("angle = "));
  print("%d\r", (servo360_getAngle(12)));
  servo360_speed(12, 720);
  pause(2000);
  print(("angle = "));
  print("%d\r", (servo360_getAngle(12)));
  servo360_speed(12, -720);
  pause(4000);
  print(("angle = "));
  print("%d\r", (servo360_getAngle(12)));
  servo360_speed(12, 360);
  pause(2000);
  servo360_enable(12, 0);

}
