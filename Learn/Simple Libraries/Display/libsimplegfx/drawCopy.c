/*
 * @file drawCopy.c
 *
 * @author Matthew Matz
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2019.  See end of file for
 * terms of use (MIT License).
 *
 * @brief This is a helper-library that allows the Propeller Multicore Microcontroller to 
 * draw text, shapes, and bitmap files on various screens and displays.
 *
 * @detail This helper-library allows the Propeller Multicore Microcontroller to 
 * draw pixels, lines, circles, recatngles, rounded rectagles, triangles, formatted text 
 * in multiple fonts, bitmap images stored on an SD card on various screens and displays. 
 * At Parallax, we would like to thank Adafruit Industries as parts of this library 
 * were dervied from the Adafruit GFX library for Arduino.  Please submit bug reports, 
 * suggestions, and improvements to this code to editor@parallax.com.
 * 
 * @note This library should not be called on its own - it is called by the display's
 * library.
 * If fonts are installed, they occupy EEPROM addresses 40576 to 63359.
 */

#include "simplegfx.h"


void drawCopy(screen_t *dev, int x, int y, int w, int h, int x0, int y0) {
  
  
  
  
  int dh = getDisplayHeight(dev);
  int dw = getDisplayWidth(dev);
  if((x  >= -w) && (x  < dw) && 
     (y  >= -h) && (y  < dh) &&
     (x0 >= -w) && (x0 < dw) && 
     (y0 >= -h) && (y0 < dh)) { // X & Y coords in bounds?
    if(y < 0) {                 // Clip top
      h += y;
      y  = 0;
    }
    if((y + h) > dh) {          // Clip bottom
      h = (dh - y);
    }     
    if(x < 0) {                 // Clip left
      w += x;
      x  = 0;
    }
    if((x + w) > dw) {          // Clip right
      w = (dw - x);
    }

    if(y0 < 0) {                // Clip top
      h += y0;
      y0  = 0;
    }
    if((y0 + h) > dh) {         // Clip bottom
      h = (dh - y0);
    }     
    if(x0 < 0) {                // Clip left
      w += x0;
      x0  = 0;
    }
    if((x0 + w) > dw) {         // Clip right
      w = (dw - x0);
    }

    int x1 = x + w;
    int y1 = y + h;
    int x2 = x0 + w;
    int y2 = y0 + h;

    if (dev->deviceCopyRect) {
      switch(dev->rotation) {
       case 0:
        dev->deviceCopyRect(dev, x, y, x1 - 1, y1 - 1, x0, y0);
        break;
       case 1:
        dev->deviceCopyRect(dev, dev->width - y1, x, dev->width - y - 1, x1 - 1, dev->width - y2, x0);
        break;
       case 2:
        dev->deviceCopyRect(dev, dev->width - x1, dev->height - y1, dev->width - x - 1, dev->height - y - 1, dev->width - x2, dev->height - y2);
        break;
       case 3:
        dev->deviceCopyRect(dev, y, dev->height - x1, y1 - 1, dev->height - x - 1, y0, dev->height - x2);
        break;
      }
      
    } else {      
      
      int tmp = 0;
      switch(dev->rotation) {
       case 0:
        x1--;
        y1--;
        x2 = x0 + w - 1;
        break;
       case 1:
        tmp = x;
        x = dev->width - y1;
        y = tmp;
        tmp = x1;
        x1 = dev->width - y - 1;
        y1 = tmp - 1;
        tmp = x0;
        x0 = dev->width - y2;
        y0 = tmp;
        x2 = x0 + w - 1;
        break;
       case 2:
        tmp = x;
        x = dev->width - x1 + 1;
        x1 = dev->width - tmp;
        tmp = y;
        y = dev->height - y1 + 1;
        y1 = dev->height - tmp;
        x0 = dev->width - x2 + 1;
        y0 = dev->height - y2 + 1;
        x2 = x0 + w - 1;
        break;
       case 3:
        x = y;
        y = dev->height - x1 + 1;
        x1 = y1;
        y1 = dev->height - x;
        x0 = y0;
        y0 = dev->height - x2 + 1;
        x2 = x0 + w;
        break;
      }
        
      unsigned int i = 0, j = 0, k = 0, l = 0;
      if (dev->color_depth == 1) {
        char tmp_img[((w * h) >> 3) + 7];
        memset(tmp_img, 0, sizeof(tmp_img));
        //print("x=%d, y=%d, w=%d, h=%d\r", x, y, w, h);
        for (j = y; j < y1; j++) {
          for (i = x; i < x1; i++) {
            unsigned char b = dev->image_ptr[(i + j * dev->width) >> 3] & (0b10000000 >> (i & 7));
            if(b) {
              tmp_img[(k >> 3)] |= (0b10000000 >> (k & 7));
              //print(".");
            } else {
              //print(" ");
            }
            print("%b", !!b);
            k++;
          }
          print("%d\r", k);
        }
        i = x0;
        j = y0;
        for (l = 0; l < k; l++) {
          unsigned char b = tmp_img[(l >> 3)] & (0b10000000 >> (l & 7));
          //print("%d", !!b);
          if(b) dev->image_ptr[(i + j * dev->width) >> 3] |=  (0b10000000 >> (i & 7));
          else  dev->image_ptr[(i + j * dev->width) >> 3] &= ~(0b10000000 >> (i & 7));
          i++;
          if (i == x2) {  // 1 to subtract off width, 1 to account for the i++ right before the test
            i = x0;
            j++;
          }
        }
      }
    }
  }    
}