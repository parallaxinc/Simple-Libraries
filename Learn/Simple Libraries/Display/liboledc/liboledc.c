/*
 * @file oledc_.c
 *
 * @author Matthew Matz
 *
 * @version 0.9
 *
 * @copyright Copyright (C) Parallax, Inc. 2016.  See end of file for
 * terms of use (MIT License).
 *
 * @brief 0.96-inch RGB OLED driver source, see oledc_.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */



#include "oledc.h"
#include "simpletools.h"

//#define TEST_IT_ALL

// Medium Fonts (include 1):

//#include "oledc_fontMediumSans.h"
//#include "oledc_fontMediumSerif.h"
//#include "oledc_fontMediumScript.h"
//#include "oledc_fontMediumBubble.h"


// Large Fonts (include 1):
 
//#include "oledc_fontLargeSans.h"
//#include "oledc_fontLargeSerif.h"
//#include "oledc_fontLargeScript.h"
//#include "oledc_fontLargeBubble.h"




int main()
{

#ifdef TEST_IT_ALL
 
  //set up the Color OLED screen
  oledc_init(7, 6, 9, 8, 5, 0); // pins: CS, D/C, DIN, CLK, RES   rotation: 0 (pins upward)
  
  ///////////////////////////// oledc_drawPixel and set_Rotation Test ////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    oledc_setRotation(r); 
    
    for(int o=0; o<oledc_getWidth(); o+=10) oledc_drawFastVLine(o, 0, oledc_getHeight(), DARKGRAY);
    for(int o=0; o<oledc_getHeight(); o+=20) oledc_drawFastHLine(0, o, oledc_getWidth(), DARKGRAY);
    pause(100);
    
    oledc_drawPixel(1, 1, WHITE);
    pause(500);
    oledc_drawPixel(20,20, WHITE);
    pause(500);
    oledc_drawPixel(30, 10, WHITE);
    pause(500);
    oledc_drawPixel(45, 150, RED);
    oledc_drawPixel(150, 45, RED);
    oledc_drawPixel(45, -45, BLUE);
    oledc_drawPixel(-45, 45, BLUE);
    
    pause(500);
    
    oledc_clear(0,0,oledc_getWidth(),oledc_getHeight());
  }    

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////// oledc_drawLine and set_Rotation Test ////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    oledc_setRotation(r); 
    
    for(int o=0; o<oledc_getWidth(); o+=10) oledc_drawFastVLine(o, 0, oledc_getHeight(), DARKGRAY);
    for(int o=0; o<oledc_getHeight(); o+=20) oledc_drawFastHLine(0, o, oledc_getWidth(), DARKGRAY);
    pause(100);
    
    oledc_drawLine(1, 1, 20,20, WHITE);
    pause(500);
    oledc_drawLine(20, 20, 30, 10, WHITE);
    pause(500);
    oledc_drawLine(30, 10, 45, 80, RED);
    oledc_drawLine(45, 80, 125, 30, RED);
    oledc_drawLine(125, 30, 45, -5, BLUE);
    oledc_drawLine(45, -5, -10, 20, BLUE);
    pause(500);
    
    oledc_clear(0,0,oledc_getWidth(),oledc_getHeight());
  }    

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// oledc_drawCircle Test ///////////////////////////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    oledc_setRotation(r); 
    
    for(int o=0; o<oledc_getWidth(); o+=10) oledc_drawFastVLine(o, 0, oledc_getHeight(), DARKGRAY);
    for(int o=0; o<oledc_getHeight(); o+=20) oledc_drawFastHLine(0, o, oledc_getWidth(), DARKGRAY);
    pause(100);
    
    oledc_drawCircle(10, 10, 5, WHITE);
    pause(500);
    oledc_drawCircle(15, 20, 10, RED);
    pause(500);
    oledc_drawCircle(20, 30, 15, YELLOW);
    pause(500);
    oledc_drawCircle(25, 40, 20, GREEN);
    pause(500);
    oledc_drawCircle(30, 50, 25, BLUE);
    pause(500);
    //pause(2000);
    
    oledc_clear(0,0,oledc_getWidth(),oledc_getHeight());
  }    

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// oledc_fillCircle Test ///////////////////////////////////////////////////////////////////////////

  for(int r = 0; r < 4; r++)
  {
    oledc_setRotation(r); 
    
    for(int o=0; o<oledc_getWidth(); o+=10) oledc_drawFastVLine(o, 0, oledc_getHeight(), DARKGRAY);
    for(int o=0; o<oledc_getHeight(); o+=20) oledc_drawFastHLine(0, o, oledc_getWidth(), DARKGRAY);
    pause(100);
    
    oledc_fillCircle(10, 10, 5, WHITE);
    pause(500);
    oledc_fillCircle(15, 20, 10, RED);
    pause(500);
    oledc_fillCircle(20, 30, 15, YELLOW);
    pause(500);
    oledc_fillCircle(25, 40, 20, GREEN);
    pause(500);
    oledc_fillCircle(30, 50, 25, BLUE);
    pause(500);
    //pause(2000);
    
    oledc_clear(0,0,oledc_getWidth(),oledc_getHeight());
  }    

  //////////////////////////////// font test //////////////////////////////////////////////////////////////////////////

  oledc_setTextColor(WHITE, WHITE);
  oledc_setRotation(0);
  
  for(int t = 33; t < 127; t++)
  {
    oledc_clear(0,0,oledc_getWidth(),oledc_getHeight());
    //pause(1);
    for(int o=0; o<oledc_getWidth(); o+=10) oledc_drawFastVLine(o, 0, oledc_getHeight(), DARKGRAY);
    for(int o=0; o<oledc_getHeight(); o+=20) oledc_drawFastHLine(0, o, oledc_getWidth(), DARKGRAY);
    oledc_setCursor(0,0,0);
    oledc_setTextSize(2);
    oledc_print("%c ", t);
    oledc_setTextSize(3);
    oledc_print("%c", t);
    pause(150);
  }    
  
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
