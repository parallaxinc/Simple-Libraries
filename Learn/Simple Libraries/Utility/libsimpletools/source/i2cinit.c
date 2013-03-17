/**
 * @file i2cinit.c
 */

#include <i2c.h>
#include "simpletools.h"

#define MAX_I2C_BUS 16

unsigned int buscnt = 0;

I2C_SIMPLE list[MAX_I2C_BUS];

I2C* i2c_newbus(int sclpin, int sdapin)
{
  I2C* bus = simple_i2cOpen(&list[buscnt++], sclpin, sdapin);
  return bus;
}  
