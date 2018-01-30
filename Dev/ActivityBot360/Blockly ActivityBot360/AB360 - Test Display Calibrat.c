/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "servo360.h"
#include "abcalibrate360.h"



// ------ Main Program ------
int main() {
  ee_getInt(32768); // NOTE: This is a temporary patch to make the AB360 robot library compile correctly.
  cal_displayData();

}
