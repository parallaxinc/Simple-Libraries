//   io control
// =================================================================================================
//
//
// =================================================================================================
#include <propeller.h>
#include "badgewxtools.h"



// ------ Buttons function ------
unsigned char buttons() {
  
  // [L touch][L NAV left][L NAV ctr][L NAV right][R NAV left][R NAV ctr][R NAV right][R touch]
  int btns = 0b00000000;
  long tDecay[2];                             // Declare tDecay variable  
  
  input(NAV_COM_L);                  // Set common lines to inputs
  input(NAV_COM_R);
  
  input(NAV_C);                      // Set pins to inputs
  input(NAV_R);

  high(NAV_L);                       // Set pin high
  
  btns |= (input(NAV_COM_L) << 6);
  btns |= (input(NAV_COM_R) << 3);
  
  input(NAV_L);
  high(NAV_C);
  
  btns |= (input(NAV_COM_L) << 5);
  btns |= (input(NAV_COM_R) << 2);
  
  input(NAV_C);
  high(NAV_R);
  
  btns |= (input(NAV_COM_L) << 4);
  btns |= (input(NAV_COM_R) << 1);
  
  input(NAV_R);
  
  low(2);
  
  high(4);
  waitcnt(CLKFREQ/4000 + CNT);
  tDecay[1] = rc_time(4,1);

  high(27);
  waitcnt(CLKFREQ/4000 + CNT);
  tDecay[0] = rc_time(27,1);
    
  btns |= ((tDecay[0] > 10 ? 1 : 0) << 7);
  btns |= ((tDecay[1] > 10 ? 1 : 0) << 0);

  return btns;
}

char button(char b) {
  // Make sure b is 0-8
  b = (b < 0 ? 0 : b);
  b = (b > 7 ? 7 : b);
  
  int m = 1 << b;
  return (buttons() & m) >> b;
}


/* 
  Terms of Use: MIT License

  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be included in all copies
  or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */