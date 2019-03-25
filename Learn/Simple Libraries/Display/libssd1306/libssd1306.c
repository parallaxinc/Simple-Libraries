


#include "simpletools.h"                      // Include simple tools
#include "ssd1306.h"


i2c *wire;
screen *bwOLED;
screen *bwOLED2;

int main()                                    // Main function

{
  //low(19);
  //high(18);
  low(26);
  low(9);
  high(8);
  pause(1000);
  wire = i2c_newbus(10, 11, 0); // sclPin, sdaPin, mode
  bwOLED2 = ssd1306_openI2C(wire, 0x3c, SSD1306_SWITCHCAPVCC, 128, 64);    // 0x3d for displays taller than 32px

  bwOLED = ssd1306_openSPI(1, 0, 2, 3, 4, SSD1306_SWITCHCAPVCC, 128, 64);

  clearDisplay(bwOLED);
  clearDisplay(bwOLED2);
  
  fillRect(bwOLED, 10,40,20,20,WHITE);
  fillRect(bwOLED, 15,45,10,10,BLACK);

  fillRect(bwOLED2, 10,40,20,20,WHITE);
  fillRect(bwOLED2, 15,45,10,10,BLACK);
 
  setTextColor(bwOLED, WHITE);
  setBgColor(bwOLED, WHITE);
  setCursor(bwOLED, 5,4,0);
  drawPrint(bwOLED, "Current Time:\r");
  setTextSize(bwOLED, MEDIUM);
  setCursor(bwOLED, 5,16,0);
  drawPrint(bwOLED, "%02d:%02d:%02d", 1, 2, 3);
  drawPixel(bwOLED, 55,60,BLACK);
  fillTriangle(bwOLED, 40,42,60,42,50,64,WHITE);
  
  updateDisplay(bwOLED2);
  updateDisplay(bwOLED);

}