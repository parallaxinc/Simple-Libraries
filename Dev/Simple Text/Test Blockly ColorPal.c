/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "colorpal.h"

// ------ Global Variables and Objects ------
colorPal *cpal15;
int Red;
int Green;
int Blue;



// ------ Main Program ------
int main() {
  cpal15 = colorPal_open(15);
  while (1) {
    colorPal_getRGB(cpal15, &Red, &Green, &Blue);
    term_cmd(CLS);
    print("%s%d", "R: ", Red);
    print("%s%d", " G: ", Green);
    print("%s%d\r", " B: ", Blue);
    pause(500);
  }

}