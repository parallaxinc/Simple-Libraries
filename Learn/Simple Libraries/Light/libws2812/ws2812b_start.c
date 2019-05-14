/**
 * @file ws2812b_start.c
 *
 * @author Parallax Inc.
 *
 * @version 0.85
 *
 * @copyright
 * Copyright (c) Parallax Inc. 2014, All Rights MIT Licensed.
 *
 * @brief Start function for WS2812B devices.
 */

#include "ws2812.h"

int ws2812b_start(ws2812_t *state)
{
  
  /*
     This is a temporary fix until a more suitable CogC
     or PASM driver replaces the existing one.  Tuning 
     actual vs. requested stays here until y = mx + b 
     is either ruled out or implemented.  
  */
  
  // usreset, ns0h, ns0l, ns1h, ns1l, int type)
  //return ws_start(state, 50, 350, 900, 900, 350, TYPE_GRB);
  
  // Actual us values suggested by DC 280, 410, 875, 875, 410

  //                            523, 1070, 1040, 563, 
  //return ws_start(state, 280, 410,  875,  875, 410, TYPE_GRB);
  //                            461, 1015,  789, 398, 
  //return ws_start(state, 280, 300,  675,  600, 260, TYPE_GRB);
  //                            375, 1250, 1160, 414, 
  //return ws_start(state, 280, 250,  600,  700, 270, TYPE_GRB);
  //                            406, 1270, 1120, 440, 
  //return ws_start(state, 280, 275,  600,  700, 270, TYPE_GRB);
  //                            411,  871,  892, 429, 
  //return ws_start(state, 280, 300,  670,  725, 275, TYPE_GRB);
  //                            418,  860,  878, 414, 
  //return ws_start(state, 280, 300,  670,  715, 265, TYPE_GRB);
  //                            404,  871,  878, 407, 
  //return ws_start(state, 280, 295,  675,  715, 265, TYPE_GRB);
  //               want       410,  875,  875,  410          
  //               measured   404,  871,  878,  408, 
  //return ws_start(state, 280, 300,  675,  715,  270, TYPE_GRB);

  // Start call suggested by MV after testing
  return ws_start(state, 300, 200,  600,  600,  200, TYPE_GRB);
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
