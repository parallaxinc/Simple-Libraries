// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {
  ee_getInt(32768); // NOTE: This is a temporary patch to make the AB360 robot library compile correctly.
  drive_speed(64, 64);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-64, 64);
  pause(700);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(64, -64);
  pause(1400);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-64, 64);
  pause(700);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-64, -64);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(96, 64);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-96, -64);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(64, 96);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);
  drive_speed(-64, -96);
  pause(2000);
  drive_speed(0, 0);
  pause(1000);

}
