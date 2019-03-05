/**
  @file i2cslave.h

  @brief Creates an I2C slave device with 32-byte registers that
  an I2C master device can write to and read from with a 7-bit
  device ID, 1-bit read/write, 8-bit register address, and 8 bits
  of data.   

  @author PASM Chris Gadd, Andy Lindsay Spin to C interface port.

  @copyright Parallax Inc. 2018, MIT License at end of file.

*/

#include "simpletools.h"

#ifndef __I2CSLAVE_H
#define __I2CSLAVE_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef struct i2cslave_struct
{
  volatile int flags;
  volatile char address;            
  volatile char pinSCL;
  volatile char pinSDA;
  char registers[32];
  volatile char cog;
} i2cslave_t;

typedef i2cslave_t i2cslave;

#endif // DOXYGEN_SHOULD_SKIP_THIS


/**
  @brief Start an I2C slave processor in a new cog.  
  
  @param pin_clock I2C bus clock pin
  
  @param pin_data I2C bus data pin
  
  @param address 7-bit I2C address for slave device.     
  
  @returns i2cslave process identifier for other i2cslave_*
           function calls.
*/  
i2cslave_t *i2cslave_open(int pin_clock, int pin_data, int address);


/**
  @brief Stop the I2C slave processor and make cog and memory resources
  available for other uses.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
*/  
void i2cslave_close(i2cslave_t *device);


/**
  @brief Provides a pointer to the first of the I2C slave device's 32 byte 
  registers.  Applications can use this address to directly access the
  registers without making method calls. 
  
  @returns char pointer to the first of 32 byte registers.
*/  
char *i2cslave_regAddr(i2cslave_t *device);


/**
  @brief Check if any registers have changed.  If a register has changed, 
  return its number.  If more than one register has changed, return the 
  highest address that has changed.  If no registers have changed, return -1.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @returns number (0 to 31) of the highest value that has changed since the 
  last checkForRegChange call.
*/  
int i2cslave_checkForRegChange(i2cslave_t *device);


/**
  @brief Get the register value if it has changed.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @param index The index (0 to 31) of the register to check.

  @returns value The new register value, or -1 if the register has not changed.
*/  
int i2cslave_checkReg(i2cslave_t *device, int index);
    

/**
  @brief Check the flags register.  Bits 31 to 0 indicate if data has changed
  in registers 31 to 0.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @returns flags Contents of the 32 bit flags register.    
*/  
int i2cslave_checkFlags(i2cslave_t *device);


/**
  @brief Check a certain register's flag.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @param index The index of the flag to be checked.
  
  @returns status 1 if the register has changed since the last time it was
  read of 0 if it has not.
*/  
int i2cslave_checkFlag(i2cslave_t *device, int index);

/**
  @brief Clear a certain register's flag.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @param index The index of the flag to be cleared.
*/  
void i2cslave_clearFlag(i2cslave_t *device, int index);


/**
  @brief Get the value stored by a certain register.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @param index The index of the register (0 to 31).
  
  @returns The value stored by the register.
*/  
char i2cslave_getReg(i2cslave_t *device, int index);


/**
  @brief Set the value of a register.
  
  @param *device The i2slave process identifier returned by i2cslave_start.
  
  @param index The index of the register (0 to 31).
  
  @param value The value stored by the register.
*/  
void i2cslave_putReg(i2cslave_t *device, int index, int value);


/**
  @brief Clear all register values and flags
  
  @param *device The i2slave process identifier returned by i2cslave_start.
*/  
void i2cslave_flush(i2cslave_t *device);


/**
  @brief Find out the highest bit with a 1 in a 32 bit register.
  
  @returns index The number of the highest bit (31 to 0) that stores a 1
  in a given 32 bit variable.
*/  
int bitwiseEncode(int i);



#ifdef __cplusplus
}
#endif
/* __cplusplus */
#endif 
/* __I2CSLAVE_H */


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
