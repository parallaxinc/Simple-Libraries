/*
 * @file putStrWithNpCVals.c
 * Function to print a string to the terminal with non printable characters
 * displayed as decimal values in brackets.
 *
 * Copyright (c) 2018, Parallax Inc.
 * Written by Andy Lindsay
 */

#include "simpletext.h"

int putStrWithNpcVals(const char *s)
{
  int size = strlen(s);
  for(int n = 0; n <= size; n++)
  {
    if(s[n] <= '~' && s[n] >= ' ')
    {
      print("%c", s[n]);
    }      
    else if(s[n] == 0)
    {
      print("[%d]", s[n]);
      break;
    }  
    else if(s[n] == '\n' || s[n] == '\r')
    {
      print("[%d]%c", s[n], s[n]);
    }      
    else
    {
      print("[%d]", s[n]);
    }   
    //pause(10);   
  }
  //pause(10);
  return size;
}

/*
+--------------------------------------------------------------------
| TERMS OF USE: MIT License
+--------------------------------------------------------------------
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+--------------------------------------------------------------------
*/


