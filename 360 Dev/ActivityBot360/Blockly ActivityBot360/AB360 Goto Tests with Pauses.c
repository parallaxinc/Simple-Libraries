// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {
  ee_getInt(32768); // NOTE: This is a temporary patch to make the AB360 robot library compile correctly.
  drive_goto(128, 128);
  pause(1000);
  drive_goto(26, -26);
  pause(1000);
  drive_goto(-52, 53);
  pause(1000);
  drive_goto(26, -26);
  pause(1000);
  drive_goto(-128, -128);
  pause(1000);
  drive_goto(192, 128);
  pause(1000);
  drive_goto(-192, -128);
  pause(1000);
  drive_goto(128, 192);
  pause(1000);
  drive_goto(-128, -192);

}
