

#include "ssd1306.h"



/*!
    @brief  Clear contents of display buffer (set all pixels to off).
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void ssd1306_clearDisplay(screen_t* dev) {
  memset(dev->image_ptr, 0, dev->image_size);
  ssd1306_updateDisplay(dev);
}

void ssd1306_resetDisplay(screen_t* dev) {
  ssd1306_clearDisplay(dev);
}  

/*!
    @brief  Push data currently in RAM to SSD1306 display.
    @return None (void).
    @note   Drawing operations are not visible until this function is
            called. Call after each graphics command, or after a whole set
            of graphics commands, as best needed by one's own application.
*/
void ssd1306_updateDisplay(screen_t* dev) {
  
  unsigned char dlist1[] = {
    SSD1306_PAGEADDR,
    0,                        // Page start address
    0xFF,                     // Page end (not really, but works here)
    SSD1306_COLUMNADDR,
    0,
    dev->width - 1
  };                          // Column start address
  
  ssd1306_writeBytes(dev, dlist1, sizeof(dlist1), 0);
  ssd1306_writeBytes(dev, dev->image_ptr, dev->image_size, 1);
}
