#include "simpletools.h"
#include "simplei2c.h"

void patch360forBlockly(void)
{
  pause(1);
  st_eeprom = i2c_newbus(28, 29, 0);
  st_eeInitFlag = 1;  
}

