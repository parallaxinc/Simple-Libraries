



/*
 * @file libil3820.c
 *
 * @author Matthew Matz & Roy Eltham
 *
 * @version 0.5
 *
 * @copyright Copyright (C) Parallax, Inc. 2018.  See end of file for
 * terms of use (MIT License).
 *
 * @brief Waveshare ePaper driver source, see il3820.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */




#include "il3820.h"
#include "simpletools.h"

//#define TEST_IT_ALL

screen *epd;


int main() 
{

  //set up the ePaper screen
  epd = il3820_init(0, 1, 2, 3, 4, 5, 128, 296);
  fillRoundRect(epd, 30, 30, 30, 30, 5, 0);
 
  setDisplayRotation(epd, 1);
  drawLine(epd, 0,0,50,0, 0);

  fillRect(epd, 20, 20, 60, 60, BLACK);

  drawRect(epd, 22, 22, 56, 56, INVERSE);
  
  fillCircle(epd, 50, 50, 20, WHITE);
  drawCircle(epd, 50, 50, 18, BLACK);
  fillCircle(epd, 50, 50, 16, BLACK);
  drawCircle(epd, 50, 50, 14, WHITE);
  
  setCursor(epd, 10, 5, 0);
  
  drawPrint(epd, "Screen Testing 0123456789");
  
  setCursor(epd, 20, 90, 0);
  setTextSize(epd, 2);
  
  drawPrint(epd, "Font Size Test");
  
  for (int t = 0; t < getDisplayHeight(epd); t+=10) {
    //drawLine(epd, t, 0, getDisplayWidth(epd) - t, getDisplayHeight(epd), INVERSE);
    //drawFastHLine(epd, 0, t, getDisplayWidth(epd), INVERSE);
  }    
  for (int t = 0; t < getDisplayWidth(epd); t+=10) {
    //drawLine(epd, t, 0, getDisplayWidth(epd) - t, getDisplayHeight(epd), INVERSE);
    //drawFastVLine(epd, t, 0, getDisplayHeight(epd), INVERSE);
  }    

  updateDisplay(epd);

#ifdef TEST_IT_ALL

  pause(2000);
  
  clearDisplay(epd);

  setDisplayRotation(epd, 0);

  for (int i = 1; i < 4; i++)
  {
      for (int r = 0; r < 4; r++)
      {
          for (int o = 0; o < getDisplayWidth(epd); o += 10) drawFastVLine(epd, o, 0, getDisplayHeight(epd), BLACK);
          for (int o = 0; o < getDisplayHeight(epd); o += 20) drawFastHLine(epd, 0, o, getDisplayWidth(epd), BLACK);

          setTextSize(epd, i);
          setTextFont(epd, r);
          setCursor(epd, 0, 0, 0);

          drawNumber(epd, 28, DEC);
          drawText(epd, " | ");
          drawNumber(epd, -28, DEC);
          drawText(epd, "\n");
          drawNumber(epd, -28, HEX);
          drawText(epd, " | ");
          drawNumber(epd, 28, BIN);
          drawNumber(epd, 28, OCT);
          drawText(epd, " | ");
          drawNumber(epd, -36.93715, 2);
          drawText(epd, "\n");
          for (int xy = 'A'; xy <= 'Z'; xy++)
          {
              drawChar(epd, xy);
          }
          updateDisplay(epd);
          pause(500);

          clearDisplay(epd);

          // small size only has one font, so skip 
          if (i == 1) r = 4;
      }
  }
  


low(27);
  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);
    
    for(int df = -20; df < 120; df += 10) il3820_drawLine(df, 40, 40, 120 - df, BLACK);
    il3820_updateDisplay();
    //pause(500);

    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }

  ///////////////////////////// il3820_drawPixel and set_Rotation Test ////////////////////////////////////////////////////
  /*
  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);
    
    il3820_drawPixel(1, 1, WHITE);

    il3820_drawPixel(20,20, WHITE);

    il3820_drawPixel(30, 10, WHITE);

    il3820_drawPixel(45, 50, BLACK);
    il3820_drawPixel(10, 45, BLACK);
    il3820_drawPixel(45, 45, BLACK);
    il3820_drawPixel(35, 45, BLACK);
    
    il3820_updateDisplay();
    pause(500);
    
    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }
*/
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////// il3820_drawLine and set_Rotation Test ////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);

    
    il3820_drawLine(1, 1, 20,20, WHITE);

    il3820_drawLine(20, 20, 30, 10, WHITE);

    il3820_drawLine(30, 10, 45, 80, BLACK);
    il3820_drawLine(45, 80, 125, 30, BLACK);
    il3820_drawLine(125, 30, 45, -5, BLACK);
    il3820_drawLine(45, -5, -10, 20, BLACK);
    
    il3820_updateDisplay();
    //pause(500);
    
    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// il3820_drawCircle Test ///////////////////////////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);
    
    il3820_drawCircle(10, 10, 5, BLACK);pause(5);
    il3820_drawCircle(15, 20, 10, BLACK);pause(5);
    il3820_drawCircle(20, 30, 15, BLACK);pause(5);
    il3820_drawCircle(25, 40, 20, BLACK);pause(5);
    il3820_drawCircle(30, 50, 25, BLACK);pause(5);
    il3820_updateDisplay();
    //pause(500);
    
    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// il3820_fillCircle Test ///////////////////////////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);

    
    il3820_fillCircle(10, 10, 5, BLACK); pause(5);
    il3820_fillCircle(15, 20, 10, BLACK);pause(5);
    il3820_fillCircle(20, 30, 15, BLACK);pause(5);
    il3820_fillCircle(25, 40, 20, BLACK);pause(5);
    il3820_fillCircle(30, 50, 25, BLACK);pause(5);
    il3820_updateDisplay();
    //pause(500);
    
    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }

  ///////////////////////////// il3820_fillRect Test ///////////////////////////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);
    
    il3820_fillRect(10, 10, 5, 5, BLACK);
    il3820_fillRect(15, 20, 10, 10, BLACK);
    il3820_fillRect(20, 30, 15, 20, BLACK);
    il3820_fillRect(25, 40, 20, 30, BLACK);
    il3820_fillRect(30, 50, 25, 40, BLACK);
    il3820_updateDisplay();
    //pause(500);
    
    il3820_clear(0,0,il3820_getWidth(),il3820_getHeight());
  }

  for(int r = 0; r < 4; r++)
  {
    il3820_setRotation(r); 
    
    for(int o=0; o<il3820_getWidth(); o+=10) il3820_drawFastVLine(o, 0, il3820_getHeight(), BLACK);
    for(int o=0; o<il3820_getHeight(); o+=20) il3820_drawFastHLine(0, o, il3820_getWidth(), BLACK);
    
    il3820_fillRoundRect(10, 10, 5, 5, 5, BLACK);
    il3820_fillRoundRect(15, 20, 10, 10, 5, BLACK);
    il3820_fillRoundRect(20, 30, 15, 20, 5, BLACK);
    il3820_fillRoundRect(25, 40, 20, 30, 5, BLACK);
    il3820_fillRoundRect(30, 50, 25, 40, 5, BLACK);
    il3820_updateDisplay();
    //pause(500);
    
    il3820_clear(0, 0, il3820_getWidth(), il3820_getHeight());
  }
  
  il3820_sleep();
  pause(2000);
  il3820_wake();

  il3820_setRotation(0);
  il3820_setTextSize(1);
  il3820_setTextFont(1);
  il3820_setCursor(0, 0, 0);
  il3820_drawText("Done.\n");
  il3820_updateDisplay();
  low(26); low(27);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TEST_IT_ALL

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