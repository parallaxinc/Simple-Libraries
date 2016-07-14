/*
 * @file oledc_bitmap.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2016.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED display bitmap driver, see oledc_h. for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */


#include "oledc.h"
#include "simpletools.h"

char TFTROTATION;

// Draw a 1-bit image (bitmap) at the specified (x,y) position
// TO DO: account for rotation 1 & 3

void oledc_bitmap(char *imgdir, int x, int y)
{
  char imgdat[200];                                 // Buffer for characters
  FILE* fp = fopen(imgdir, "r");                // Reopen file for reading

  fread(imgdat, 1, 30, fp);                        // Read 30 characters
  

  int img_width = imgdat[18];
  int img_height = imgdat[22];
  int img_offset = imgdat[10];
  fread(imgdat, 1, img_offset - 30, fp);

  for (int k = 0; k < img_height - 1; k++)
  {
    if (TFTROTATION == 2) oledc_goTo(-x + TFTWIDTH - img_width, -y + k + (TFTHEIGHT - img_height));
    if (TFTROTATION == 0) oledc_goTo(x, y + img_height - k - 1);
    
    int j = 1;
    fread(imgdat, 1, img_width * 2, fp);
    for (int w = 0; w < img_width; w++)
    {
      int p;
      if (TFTROTATION == 2) p = img_width * 2 - j;
      if (TFTROTATION == 0) p = j;
      
      if (TFTROTATION == 1) 
      {
        oledc_goTo(TFTWIDTH - y - img_height + k, x + w);
        p = j;
      }   
      if (TFTROTATION == 3)
      {
        oledc_goTo(y + k, TFTHEIGHT - x - img_width + w);
      }             

      oledc_writeData(imgdat[p]);
      oledc_writeData(imgdat[p - 1]);
      j += 2;
    }
  }
  fclose(fp);                                 // Close the file
}

/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
