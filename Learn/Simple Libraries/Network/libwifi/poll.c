/*
  @file poll.c

  @author Andy Lindsay

  @version 0.80 for firmware 1.0

  @copyright
  Copyright (C) Parallax, Inc. 2017. All Rights MIT Licensed.

  @brief API for the Parallax WX Wi-Fi Module ESP8266-WROOM-02.
*/


#include "simpletools.h"
#include "fdserial.h"
#include "wifi.h"


int  wifi_replyStringIn(int maxByteCount);
void wifi_replyStringDisplay(char *s);
void wifi_simpletermSuspend(void);
void wifi_simpletermResume(void);
int wifi_replyStringInAlt(char *buffer, int maxByteCount);


fdserial *wifi_fds;
int wifi_pin_do;
int wifi_pin_di;
int wifi_baud;
int wifi_comSelectPin;

int simpleterm_toRxDi;
int simpleterm_fromTxDo;
int wifi_msReplyTimeout;

char wifi_event;
char wifi_status;
int wifi_id;
int wifi_handle;

int wifi_timeoutFlag; 

char *wifi_buf;
int wifi_buf_size;


void wifi_poll(int *event, int *id, int *handle)
{
  #ifdef WIFI_DEBUG
  print("wifi_poll\r");
  #endif  //WIFI_DEBUG

  wifi_simpletermSuspend();

  dprint(wifi_fds, "%c%c\r", CMD, POLL);
  //wifi_replyStringIn(wifi_buf_size - 1);      
  char buffer[32];
  memset(buffer, 0, 32);
  wifi_replyStringInAlt(buffer, sizeof(buffer) - 1);

  sscan(&buffer[2], "%c%d%d", &wifi_event, &wifi_handle, &wifi_id);

  wifi_simpletermResume();

  *event = wifi_event;
  *handle = wifi_handle;
  *id = wifi_id;
} 

int wifi_replyStringInAlt(char *buffer, int maxByteCount)
{
  wifi_timeoutFlag = 0;
  int n = 0;
  buffer[n] = 0;

  volatile int dt = CLKFREQ;
  volatile int t = CNT;
  while(1) 
  {
    if((CNT - t) > dt)
    {
      wifi_timeoutFlag = 1;
      break;
    }      
    if(fdserial_rxCount(wifi_fds) > 0)
    {
      buffer[n] = fdserial_rxChar(wifi_fds);
      n++;
      buffer[n] = 0;
      if( (buffer[n-1] == '\r') || (n == maxByteCount - 1) ) break;
    }
  } 
  return n;
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

