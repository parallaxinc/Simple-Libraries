// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abdrive360.h"



// ------ Main Program ------
int main() {

  // Drive Speeds
  drive_goto(256, 256);
  pause(200);
  drive_goto(26, -25);

}
