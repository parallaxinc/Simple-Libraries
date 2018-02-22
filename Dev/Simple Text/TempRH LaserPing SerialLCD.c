// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "dht22.h"

// ------ Function Declarations ------
int constrain(int __cVal, int __cMin, int __cMax);

// ------ Main Program ------
int main() {
  serial *debug_lcd = serial_open(17, 17, 0, 2400);

  // ERROR: LCD is not initialized!
  while (1) {
    dht22_read(8);
    writeChar(debug_lcd, 12);
    pause(5);
    writeChar(debug_lcd, 215);
    writeChar(debug_lcd, 212);
    writeChar(debug_lcd, 223);
    writeChar(debug_lcd, (128 + (constrain(0, 0, 3) * 20) + constrain(0, 0, 19)));
    dprint(debug_lcd, "%s%04.1f", "Temp F = ", ((float) dht22_getTemp(FAHRENHEIT)) / 10.0);
    writeChar(debug_lcd, (128 + (constrain(1, 0, 3) * 20) + constrain(0, 0, 19)));
    dprint(debug_lcd, "%s%04.1f", "RH % = ", ((float) dht22_getHumidity()) / 10.0);
    if (dht22_getTemp(FAHRENHEIT) > 111) {
      writeChar(debug_lcd, (128 + (constrain(2, 0, 3) * 20) + constrain(0, 0, 19)));
      writeChar(debug_lcd, 218);
      writeChar(debug_lcd, 209);
      writeChar(debug_lcd, 230);
      dprint(debug_lcd, "0");
    }

    pause(30000);
  }

}

// ------ Functions ------
int constrain(int __cVal, int __cMin, int __cMax) {
  if (__cVal < __cMin) __cVal = __cMin;
  if (__cVal > __cMax) __cVal = __cMax;
  return __cVal;
}