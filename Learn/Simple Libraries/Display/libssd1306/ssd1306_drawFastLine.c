
#include "ssd1306.h"



void ssd1306_drawFastHLine(screen_t* dev, int x, int y, int w, int color) {
  unsigned char *pBuf = &dev->image_ptr[(y >> 3) * dev->width + x],
           mask = 1 << (y & 7);
  switch(color) {
   case BLACK: mask = ~mask; while(w--) { *pBuf++ &= mask; }; break;
   case INVERSE:             while(w--) { *pBuf++ ^= mask; }; break;
   default:                  while(w--) { *pBuf++ |= mask; }; break;
  }
}


void ssd1306_drawFastVLine(screen_t* dev, int x, int __y, int __h, int color) {

  if(__h > 0) { // Proceed only if height is now positive
    // this display doesn't need ints for coordinates,
    // use local byte registers for faster juggling
    unsigned char  y = __y, h = __h;
    unsigned char *pBuf = &dev->image_ptr[(y >> 3) * dev->width + x];

    // do the first partial byte, if necessary - this requires some masking
    unsigned char mod = (y & 7);
    if(mod) {
      // mask off the high n bits we want to set
      mod = 8 - mod;
      // lookup table results in a nearly 10% performance
      // improvement in fill* functions
      unsigned char premask[8] = { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
      unsigned char mask = premask[mod];
      // adjust the mask if we're not going to reach the end of this byte
      if(h < mod) mask &= (0XFF >> (mod - h));

      switch(color) {
       case BLACK:   *pBuf &= ~mask; break;
       case INVERSE: *pBuf ^=  mask; break;
       default:      *pBuf |=  mask; break;
      }
      pBuf += dev->width;
    }

    if(h >= mod) { // More to go?
      h -= mod;
      // Write solid bytes while we can - effectively 8 rows at a time
      if(h >= 8) {
        if(color == INVERSE) {
          // separate copy of the code so we don't impact performance of
          // black/white write version with an extra comparison per loop
          do {
            *pBuf ^= 0xFF;  // Invert byte
            pBuf  += dev->width; // Advance pointer 8 rows
            h     -= 8;     // Subtract 8 rows from height
          } while(h >= 8);
        } else {
          // store a local value to work with
          unsigned char val = (color != BLACK) ? 255 : 0;
          do {
            *pBuf = val;    // Set byte
            pBuf += dev->width;  // Advance pointer 8 rows
            h    -= 8;      // Subtract 8 rows from height
          } while(h >= 8);
        }
      }

      if(h) { // Do the final partial byte, if necessary
        mod = h & 7;
        // this time we want to mask the low bits of the byte,
        // vs the high bits we did above
        // lookup table results in a nearly 10% performance
        // improvement in fill* functions
        unsigned char postmask[8] = { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
        unsigned char mask = postmask[mod];
        switch(color) {
         case BLACK:   *pBuf &= ~mask; break;
         case INVERSE: *pBuf ^=  mask; break;
         default:      *pBuf |=  mask; break;
        }
      }
    }
  } // endif positive height
}
