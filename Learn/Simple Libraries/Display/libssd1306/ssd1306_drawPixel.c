

#include "ssd1306.h"


/*!
    @brief  Set/clear/invert a single pixel. This is also invoked by the
            Adafruit_GFX library in generating many higher-level graphics
            primitives.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @param  color
            Pixel color, one of: BLACK, WHITE or INVERT.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void ssd1306_drawPixel(screen_t* dev, int x, int y, int color) {
  if((x >= 0) && (x < dev->width) && (y >= 0) && (y < dev->height)) {
    // Pixel is in-bounds. Rotate coordinates if needed.
    switch(dev->rotation) {
     case 1:
      gfx_swap(x, y);
      x = dev->width - x - 1;
      break;
     case 2:
      x = dev->width  - x - 1;
      y = dev->height - y - 1;
      break;
     case 3:
      gfx_swap(x, y);
      y = dev->height - y - 1;
      break;
    }
    switch(color) {
     case BLACK:   dev->image_ptr[x + (y >> 3) * dev->width] &= ~(1 << (y & 7)); break;
     case INVERSE: dev->image_ptr[x + (y >> 3) * dev->width] ^=  (1 << (y & 7)); break;
     default:      dev->image_ptr[x + (y >> 3) * dev->width] |=  (1 << (y & 7)); break;
    }
  }
}

/*!
    @brief  Return color of a single pixel in display buffer.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @return true if pixel is set (usually WHITE, unless display invert mode
            is enabled), false if clear (BLACK).
    @note   Reads from buffer contents; may not reflect current contents of
            screen if display() has not been called.
*/
int ssd1306_getPixel(screen_t* dev, int x, int y) {
  if((x >= 0) && (x < dev->width) && (y >= 0) && (y < dev->height)) {
    // Pixel is in-bounds. Rotate coordinates if needed.
    switch(dev->rotation) {
     case 1:
      gfx_swap(x, y);
      x = dev->width - x - 1;
      break;
     case 2:
      x = dev->width  - x - 1;
      y = dev->height - y - 1;
      break;
     case 3:
      gfx_swap(x, y);
      y = dev->height - y - 1;
      break;
    }
    return (dev->image_ptr[x + (y / 8) * dev->width] & (1 << (y & 7)));
  }
  return -1; // Pixel out of bounds
}

/*!
    @brief  Get base address of display buffer for direct reading or writing.
    @return Pointer to an unsigned 8-bit array, column-major, columns padded
            to full byte boundary if needed.
*/
unsigned char* ssd1306_getImageBuffer(screen_t* dev) {
  return dev->image_ptr;
}
