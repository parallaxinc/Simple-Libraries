//
// automatically generated by spin2cpp v1.93 on Sun Aug 16 16:35:52 2015
// spin2cpp --ccode --main IrApp.spin 
//

//   MMA7660 accelerometer
// =================================================================================================
//
//   File....... jm_ir_hdserial.spin
//   Purpose.... Half-duplex, true-mode serial IO or IR
//   Author..... Jon "JonnyMac" McPhalen 
//               Copyright (c) 2009-2015 Jon McPhalen
//               -- see below for terms of use
//   E-mail..... jon@jonmcphalen.com
//   Started.... 
//   Updated.... 28 JUL 15
//
// =================================================================================================
/* 

    Example IR Connections
 
              ┌───┐
              │(*)│ 3.3-5v (device dependent)
              └┬┬┬┘ 
         rx ──┘│└──┘
                


              IR
      3.3v ──────┐
                    │
        tx ──────┘
               33


              33  IR
        tx ───────┐
                            

 */
#include <stdlib.h>
#include <propeller.h>
#include "badgewxtools.h"

/*
#ifdef __GNUC__
#define INLINE__ static inline
#define Yield__() __asm__ volatile( "" ::: "memory" )
//define PostEffect__(X, Y) __extension__({ int32_t tmp__ = (X); (X) = (Y); tmp__; })
#else
#define INLINE__ static
static int32_t tmp__;
#define PostEffect__(X, Y) (tmp__ = (X), (X) = (Y), tmp__)
#define Yield__()
#define waitcnt(n) _waitcnt(n)
#define coginit(id, code, par) _coginit((unsigned)(par)>>2, (unsigned)(code)>>2, id)
#define cognew(code, par) coginit(0x8, (code), (par))
#define cogstop(i) _cogstop(i)
#endif
*/

static uint8_t dat[] = {
  0xf0, 0xb1, 0xbc, 0xa0, 0x58, 0x90, 0xbc, 0xa0, 0x04, 0xb0, 0xfc, 0x80, 0x58, 0x92, 0xbc, 0xa0, 
  0x04, 0xb0, 0xfc, 0x80, 0x58, 0x94, 0xbc, 0x08, 0x04, 0xb0, 0xfc, 0x80, 0x58, 0x96, 0xbc, 0xa0, 
  0x04, 0xb0, 0xfc, 0x80, 0x58, 0x98, 0xbc, 0xa0, 0x04, 0xb0, 0xfc, 0x80, 0x58, 0x9a, 0xbc, 0x08, 
  0x04, 0xb0, 0xfc, 0x80, 0x58, 0xb2, 0xbc, 0x08, 0x01, 0x9c, 0xfc, 0xa0, 0x59, 0x9c, 0xbc, 0x2c, 
  0x4e, 0xec, 0xbf, 0x64, 0x04, 0xb0, 0xfc, 0x80, 0x58, 0xb2, 0xbc, 0x08, 0x01, 0x9e, 0xfc, 0xa0, 
  0x59, 0x9e, 0xbc, 0x2c, 0x4f, 0xec, 0xbf, 0x64, 0x04, 0xb0, 0xfc, 0x80, 0x58, 0xa0, 0xbc, 0x08, 
  0x50, 0xa2, 0xbc, 0xa0, 0x01, 0xa2, 0xfc, 0x28, 0x50, 0xa2, 0xbc, 0x80, 0x04, 0xb0, 0xfc, 0x80, 
  0x58, 0xf4, 0xbf, 0x08, 0x46, 0xb2, 0xbc, 0x68, 0x59, 0xf0, 0xbf, 0xa0, 0xf1, 0xa9, 0xbc, 0xa0, 
  0xf2, 0x9d, 0x3c, 0x61, 0x32, 0x00, 0x70, 0x5c, 0x51, 0xa8, 0xbc, 0x80, 0x00, 0xa4, 0xfc, 0xa0, 
  0x08, 0xa6, 0xfc, 0xa0, 0x50, 0xa8, 0xbc, 0xf8, 0xf2, 0x9d, 0x3c, 0x61, 0x01, 0xa4, 0xfc, 0x28, 
  0x80, 0xa4, 0xfc, 0x70, 0x25, 0xa6, 0xfc, 0xe4, 0x4e, 0x9c, 0x3c, 0xf0, 0x48, 0xb0, 0xbc, 0x08, 
  0x4a, 0xb0, 0xbc, 0x80, 0x58, 0xa4, 0x3c, 0x00, 0x4a, 0xb0, 0xbc, 0x84, 0x01, 0xb0, 0xfc, 0x80, 
  0x7f, 0xb0, 0xfc, 0x60, 0x48, 0xb0, 0x3c, 0x08, 0x4b, 0xb0, 0xbc, 0x08, 0x4c, 0xb2, 0xbc, 0x08, 
  0x59, 0xb0, 0x3c, 0x86, 0x1f, 0x00, 0x68, 0x5c, 0x4d, 0xb0, 0xbc, 0xa0, 0x59, 0xb0, 0xbc, 0x80, 
  0x58, 0xaa, 0xbc, 0x00, 0x01, 0xb2, 0xfc, 0x80, 0x7f, 0xb2, 0xfc, 0x60, 0x4c, 0xb2, 0x3c, 0x08, 
  0x47, 0xaa, 0xbc, 0x68, 0x01, 0xaa, 0xfc, 0x2c, 0x0b, 0xac, 0xfc, 0xa0, 0x50, 0xae, 0xbc, 0xa0, 
  0xf1, 0xaf, 0xbc, 0x80, 0x01, 0xaa, 0xfc, 0x29, 0x4f, 0xec, 0xbf, 0x74, 0x50, 0xae, 0xbc, 0xf8, 
  0x41, 0xac, 0xfc, 0xe4, 0x32, 0x00, 0x7c, 0x5c, 0x00, 0x00, 0x00, 0x10, 0x00, 0xff, 0xff, 0xff, 
};

jm_ir_hdserial hdserial;
jm_ir_hdserial *irself;

int32_t ircom_start(int32_t rxd, int32_t txd, int32_t baud, int32_t freq)
{
  irself = &hdserial;
  
  int32_t _parm__0009[4];
  _parm__0009[0] = rxd;
  _parm__0009[1] = txd;
  _parm__0009[2] = baud;
  _parm__0009[3] = freq;
  // Half-duplex, true mode UART 
  // -- rxd is rx pin (in)
  // -- txd is tx pin (out)
  // -- baud is baud rate for coms (2400 suggested)
  // -- freq is IR modulation frequency (e.g., 38000)
  // stop UART driver
  ircom_stop();
  // clear (for restart)
  memset( (void *)&irself->rxhead, 0, sizeof(int32_t)*6);
  // provide buffer locations                                              
  irself->rxhub = (int32_t)(&irself->rxbuf[0]);
  irself->txhub = (int32_t)(&irself->txbuf[0]);
  // copy pins
  memmove( (void *)&irself->rxpin, (void *)&_parm__0009[0], 4*(2));
  // set bit time for baud rate
  irself->bitticks = CLKFREQ / _parm__0009[2];
  // modulation setup              
  irself->frsetup = ((int32_t)0x80000000U / (CLKFREQ / _parm__0009[3])) << 1;
  // disable pins in calling cog
  DIRA &= ~(1<<_parm__0009[0]);
  DIRA &= ~(1<<_parm__0009[1]);
  // start UART cog
  irself->cog = cognew((int32_t)(&(*(int32_t *)&dat[0])), (int32_t)(&irself->rxhead)) + 1;
  return irself->cog;
}

/* 

  Copyright (C) 2009-2015 Jon McPhalen

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
