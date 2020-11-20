/*
  i2cslave.c
  Source file for the i2cslave library functions
  @author Andy Lindsay
  @copyright Parallax Inc. 2018, MIT License at end of file.
*/

#include "simpletools.h"
#include "i2cslave.h"


i2cslave_t *i2cslave_open(int pin_clock, int pin_data, int address)
{
  i2cslave_t *device;
  device = (void *) malloc(sizeof(i2cslave_t));
  device->address = address;
  device->pinSCL = pin_clock;
  device->pinSDA = pin_data;
  
  if(device->cog == 0)
  {
    extern int binary_I2C_slave_v1_2_dat_start[]; 
    device->cog = 1 + cognew((void*)binary_I2C_slave_v1_2_dat_start, (void*)device);
  }
  return device;
}      
  

void i2cslave_close(i2cslave_t *device)
{
  if(device->cog > 0)
  {
    cogstop(device->cog - 1);
    device->cog = 0;
    free(device);
  }  
}


char *i2cslave_regAddr(i2cslave_t *device)
{
  return device->registers;
}


int i2cslave_checkForRegChange(i2cslave_t *device)
{
  int index = bitwiseEncode(device->flags) - 1;
  if(index != -1) i2cslave_clearFlag(device, index);
  return index;
}  


int i2cslave_checkReg(i2cslave_t *device, int index)
{
  int mask = 1 << index;
  if(mask & device->flags)
  {
    i2cslave_clearFlag(device, index);
    return device->registers[index];
  }
  else
  {
    return -1;
  }
}          
    

int i2cslave_checkFlags(i2cslave_t *device)
{
  return device->flags;
}  


int i2cslave_checkFlag(i2cslave_t *device, int index)
{
  return (device->flags >> index) & 1;
}


void i2cslave_clearFlag(i2cslave_t *device, int index)
{
  device->flags = device->flags & (!(1<<index));
}


char i2cslave_getReg(i2cslave_t *device, int index)
{
  int rval = (int) device->registers[index];
  i2cslave_clearFlag(device, index);
  return rval;
}


void i2cslave_putReg(i2cslave_t *device, int index, int value)
{
  device->registers[index] = value;
}


void i2cslave_flush(i2cslave_t *device)
{
  device->flags = 0;
  memset(device->registers, 0, 32);
}    


int bitwiseEncode(int i)
{
  int mask = 1 << 31;
  int n;
  for(n = 32; n > 0; n--)
  {
    if(i & mask)
    {
      break;
    }
    mask >>= 1;      
  }
  return n;
}  



/**
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

