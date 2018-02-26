/* SERIAL_TERMINAL USED */
// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "colorpal.h"

// ------ Global Variables and Objects ------
colorPal *cpal6;
int R;
int G;
int B;



// ------ Main Program ------
int main() {
  cpal6 = colorPal_open(6);
  while(1) {
    colorPal_getRGB(cpal6, &R, &G, &B);print("%s%d", "R: ", R);
    print("%s%d", ", G: ", G);
    print("%s%d\r", ", B: ", B);
    pause(1000);
  }

}
