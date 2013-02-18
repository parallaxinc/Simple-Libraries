/*
  Preliminary library code based on David Betz' code from
  compass code from code.google.com/p/propgcc.
*/

#include "compass3d.h"
#include "simpletools.h"

uint8_t continuous_mode[] = { 0x02, 0x00 };

void CompassInit(I2C *bus)
{
  /* set to continuous mode */
  if (i2cWrite(bus, 0x3C, continuous_mode, sizeof(continuous_mode), 1) != 0)
  printf("Setting continuous mode failed\n");
}

uint8_t read_data_registers[] = { 0x03 };

void CompassRead(I2C *bus, int *px, int *py, int *pz)
{
  int16_t x16, y16, z16;
  uint8_t data[6];
    
  /* select the data registers */
  if (i2cWrite(bus, 0x3C, read_data_registers, sizeof(read_data_registers), 1) != 0)
  printf("Write failed\n");
    
  /* read the data registers */
  if (i2cRead(bus, 0x3D, data, sizeof(data), 1) != 0)
  printf("Read failed\n");

  /* assemble the return values */
  x16 = (data[0] << 8) | data[1];
  z16 = (data[2] << 8) | data[3];
  y16 = (data[4] << 8) | data[5];
    
  /* return the signed values */
  *px = x16;
  *py = y16;
  *pz = z16;
}
