
#include "ssd1306.h"


/*!
    @brief  Activate a diagonal scroll for all or part of the display.
    @param  start
            First row.
    @param  stop
            Last row.
    @return None (void).
*/
void ssd1306_scroll(screen_t* dev, char start, char stop, char action) {
  if (action != SSD1306_DEACTIVATE_SCROLL) {
    if (action == SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL ||
        action == SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL) {
      unsigned char scrollListA[] = {
        SSD1306_SET_VERTICAL_SCROLL_AREA,
        0x00,
        dev->height
      };
      ssd1306_writeBytes(dev, scrollListA, sizeof(scrollListA), 0);
      ssd1306_write(dev, dev->height, 0);
    }    
    unsigned char scrollListB[] = {
      action,
      0x00 };
    ssd1306_writeBytes(dev, scrollListB, sizeof(scrollListB), 0);
    ssd1306_write(dev, start, 0);
    ssd1306_write(dev, 0x00, 0);
    ssd1306_write(dev, stop, 0);
    unsigned char scrollListC[] = {
      0x01,
      SSD1306_ACTIVATE_SCROLL };
    ssd1306_writeBytes(dev, scrollListC, sizeof(scrollListC), 0);
  } else {
    ssd1306_write(dev, SSD1306_DEACTIVATE_SCROLL, 0);  
  }
}

/*!
    @brief  Enable or disable display invert mode (white-on-black vs
            black-on-white).
    @param  i
            If true, switch to invert mode (black-on-white), else normal
            mode (white-on-black).
    @return None (void).
    @note   This has an immediate effect on the display, no need to call the
            display() function -- buffer contents are not changed, rather a
            different pixel mode of the display hardware is used. When
            enabled, drawing BLACK (value 0) pixels will actually draw white,
            WHITE (value 1) will draw black.
*/
void ssd1306_invertDisplay(screen_t* dev, char i) {
  ssd1306_write(dev, i ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY, 0);
}

/*!
    @brief  Dim the display.
    @param  dim
            true to enable lower brightness mode, false for full brightness.
    @return None (void).
    @note   This has an immediate effect on the display, no need to call the
            display() function -- buffer contents are not changed.
*/
void ssd1306_dimDisplay(screen_t* dev, char dim) {
  unsigned char contrast;

  if(dim) contrast = 0; // Dimmed display
  else    contrast = (dev->status_pin == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF;
  
  ssd1306_write(dev, SSD1306_SETCONTRAST, 0);
  ssd1306_write(dev, contrast, 0);
}