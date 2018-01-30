// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {
  ee_getInt(32768); // NOTE: This is a temporary patch to make the AB360 robot library compile correctly.
  drive_goto(128, 128);
  pause(1000);
  drive_goto(-25, 25);
  pause(1000);
  drive_goto(50, -50);
  pause(1000);
  drive_goto(-25, 25);
  pause(1000);
  drive_goto(-128, -128);
  pause(1000);
  drive_goto(128, 192);
  pause(1000);
  drive_goto(-128, -192);
  pause(1000);
  drive_goto(192, 128);
  pause(1000);
  drive_goto(-192, -128);

}
