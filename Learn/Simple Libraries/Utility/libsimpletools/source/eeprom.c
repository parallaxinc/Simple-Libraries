/**
 * @file eeprom.c
 *
 * @author Andy Lindsay
 *
 * @version dev001
 *
 * @copyright Copyright (C) Parallax, Inc. 2013.  See end of file for
 * terms of use (MIT License).
 *
 * @brief eeprom functions source, see simpletools.h for documentation.
 *
 * @detail Please submit bug reports, suggestions, and improvements to
 * this code to editor@parallax.com.
 */

#include "simpletools.h"                      // simpletools function prototypes

static I2C* eeprom;

int ee_Init()
{
  eeprom = i2cBootOpen();
  if ( eeprom == 0 ) {
      return -1;
  }
  return 0;
}

void ee_put_byte(char value, int addr)
{
  if(!eeprom) ee_Init();
  char  data[3] = { addr >> 8, addr & 0xFF, value };
  while(i2cWrite(eeprom, EEPROM_ADDR, data, 3, 1));
}

char ee_get_byte(int addr)
{
  if(!eeprom) ee_Init();
  char data[2] = { addr >> 8, addr & 0xFF };
  char value;
  while(i2cWrite(eeprom, EEPROM_ADDR, data, 2, 0));
  while(i2cRead(eeprom, EEPROM_ADDR, &value, 1, 1)); 
  return value;
}

void ee_put_int(int value, int addr)
{
  if(!eeprom) ee_Init();
  char  data[6] = { addr >> 8, addr & 0xFF, 
                      (char)(value & 0xFF), (char)((value >> 8) & 0xFF), 
                      (char)((value >> 16) & 0xFF), (char)((value >> 24) & 0xFF) };
  while(!i2cWrite(eeprom, EEPROM_ADDR, data, 6, 1));
}

int ee_get_int(int addr)
{
   if(!eeprom) ee_Init();
   char  data[2] = { addr >> 8, addr & 0xFF };
   char  value[4];
   while(i2cWrite(eeprom, EEPROM_ADDR, data, 2, 1));
   while(i2cRead(eeprom, EEPROM_ADDR, value, 4, 0)); 
   int result = ((int) value[3] << 24) | ((int) value[2] << 16) | 
                ((int) value[1] << 8) | (int) value[0];
   return result;
}

void ee_put_float32(float value, int addr)
{
  if(!eeprom) ee_Init();
  char  data[6] = { addr >> 8, addr & 0xFF, 
                      ((char) value & 0xFF), (((char) value >> 8) & 0xFF), 
                      (((char) value >> 16) & 0xFF), (((char) value >> 24) & 0xFF) };
  while(!i2cWrite(eeprom, EEPROM_ADDR, data, 6, 1));
}

float ee_get_float32(int addr)
{
   if(!eeprom) ee_Init();
   char  data[2] = { addr >> 8, addr & 0xFF };
   char  value[4];
   while(i2cWrite(eeprom, EEPROM_ADDR, data, 2, 1));
   while(i2cRead(eeprom, EEPROM_ADDR, value, 4, 0)); 
   float result = ((int) value[3] << 24) | ((int) value[2] << 16) | 
                ((int) value[1] << 8) | (int) value[0];
   return result;
}

char* ee_get_str(char* s, int n, int addr)
{
  if(!eeprom) ee_Init();
  int i;
  for(i = 0; i < n; i++)
  {
    s[i] = ee_get_byte(addr+i);
  }
  return s;
}

void ee_put_str(char* s, int n, int addr)
{
  if(!eeprom) ee_Init();
  int i;
  for(i = 0; i < n; i++)
  {
    ee_put_byte(s[i], addr+i);
  }
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
