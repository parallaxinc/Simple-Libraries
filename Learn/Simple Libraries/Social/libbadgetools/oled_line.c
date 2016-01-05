#include <stdlib.h>
#include <propeller.h>
#include "badgetools.h"

volatile screen *self;

void line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t c)
{
  int32_t _parm__0015[12];
  _parm__0015[0] = x0;
  _parm__0015[1] = y0;
  _parm__0015[2] = x1;
  _parm__0015[3] = y1;
  _parm__0015[4] = c;
  // Draws a line on the screen
  // Adapted/converted from psuedo-code found on Wikipedia:
  // http://en.wikipedia.org/wiki/Bresenham's_line_algorithm      
  _parm__0015[5] = -((abs((_parm__0015[3] - _parm__0015[1]))) > (abs((_parm__0015[2] - _parm__0015[0]))));
  if (_parm__0015[5]) {
    screen_swap((int32_t)(&_parm__0015[0]), (int32_t)(&_parm__0015[1]));
    screen_swap((int32_t)(&_parm__0015[2]), (int32_t)(&_parm__0015[3]));
  }
  if (_parm__0015[0] > _parm__0015[2]) {
    screen_swap((int32_t)(&_parm__0015[0]), (int32_t)(&_parm__0015[2]));
    screen_swap((int32_t)(&_parm__0015[1]), (int32_t)(&_parm__0015[3]));
  }
  _parm__0015[6] = _parm__0015[2] - _parm__0015[0];
  _parm__0015[7] = abs((_parm__0015[3] - _parm__0015[1]));
  _parm__0015[8] = _parm__0015[6] << 1;
  _parm__0015[10] = _parm__0015[1];
  if (_parm__0015[1] < _parm__0015[3]) {
    _parm__0015[9] = 1;
  } else {
    _parm__0015[9] = -1;
  }
  {
    int32_t _limit__0041 = _parm__0015[2];
    int32_t _step__0042 = 1;
    _parm__0015[11] = _parm__0015[0];
    if (_parm__0015[11] >= _limit__0041) _step__0042 = -_step__0042;
    do {
      if (_parm__0015[5]) {
        point(_parm__0015[10], _parm__0015[11], _parm__0015[4]);
      } else {
        point(_parm__0015[11], _parm__0015[10], _parm__0015[4]);
      }
      _parm__0015[8] = _parm__0015[8] - _parm__0015[7];
      if (_parm__0015[8] < 0) {
        _parm__0015[10] = _parm__0015[10] + _parm__0015[9];
        _parm__0015[8] = _parm__0015[8] + _parm__0015[6];
      }
      _parm__0015[11] = _parm__0015[11] + _step__0042;
    } while (((_step__0042 > 0) && (_parm__0015[11] <= _limit__0041)) || ((_step__0042 < 0) && (_parm__0015[11] >= _limit__0041)));
  }
  if (self->AutoUpdate) screen_update();
  //return 0;
}

/*
  TERMS OF USE: MIT License
 
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/

