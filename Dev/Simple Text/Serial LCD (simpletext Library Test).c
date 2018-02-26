// ------ Libraries and Definitions ------
#include "simpletools.h"

// ------ Function Declarations ------
int constrain(int __cVal, int __cMin, int __cMax);

// ------ Main Program ------
int main() {
  serial *debug_lcd = serial_open(17, 17, 0, 2400);

  // ERROR: LCD is not initialized!
  writeChar(debug_lcd, 22);
  pause(5);
  writeChar(debug_lcd, 12);
  pause(5);
  dprint(debug_lcd, "Hello");
  writeChar(debug_lcd, 17);
  pause(5);
  writeChar(debug_lcd, 217);
  writeChar(debug_lcd, 210);
  writeChar(debug_lcd, 223);
  pause(1000);
  writeChar(debug_lcd, 216);
  writeChar(debug_lcd, 210);
  writeChar(debug_lcd, 223);
  writeChar(debug_lcd, 18);
  pause(5);
  pause(2000);
  writeChar(debug_lcd, 13);
  pause(5);
  dprint(debug_lcd, "%s%d", "Hello ", 123);
  pause(1500);
  writeChar(debug_lcd, 12);
  pause(5);
  writeChar(debug_lcd, (128 + (constrain(2, 0, 3) * 20) + constrain(5, 0, 19)));
  dprint(debug_lcd, "%s%d", "Goodbye", 321);
  pause(1000);

}

// ------ Functions ------
int constrain(int __cVal, int __cMin, int __cMax) {
  if (__cVal < __cMin) __cVal = __cMin;
  if (__cVal > __cMax) __cVal = __cMax;
  return __cVal;
}