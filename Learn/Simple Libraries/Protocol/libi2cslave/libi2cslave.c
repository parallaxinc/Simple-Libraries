/*
  libi2slave.c
  
  Test harness application makes the Propeller chip an I/O expander.
  
  This example is available for user editing in 
    ..\Documents\SimpleIDE\Learn\Examples\Protocols\I2C Slave IO Expander.side
     
*/

#include "simpletools.h"
#include "simplei2c.h"
#include "i2cslave.h"

#define COMMAND 0
#define PIN1 1
#define PIN2 2
#define STATE 3
#define ARG1 4
#define ARG2 8
#define ARG3 12
#define ARG4 16
#define ARG5 20
#define RETVAL 24

#define HIGH 1
#define LOW 2
#define INPUT 3
#define TOGGLE 4
#define SETDIR 5
#define GETDIR 6
#define SETOUTPUT 7
#define GETOUTPUT 8

#define PAUSE 9
#define PULSIN 10
#define PULSOUT 11
#define COUNT 12
#define FREQOUT 13
#define RCTIME 16

i2c *mbBusM;
i2cslave *mbBusS;
static char *reg;

void i2cMaster()
{
  mbBusM = i2c_newbus(8,  9,   0);
  reg = i2cslave_regAddr(mbBusS);

  char command, pin;
  int arg1, arg2;
  
  pause(100);
  
  command = FREQOUT; pin = 4; arg1 = 2000; arg2 = 3000;
  i2c_out(mbBusM, 0x42, ARG2, 1, (unsigned char *) &arg2, 4);
  i2c_out(mbBusM, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
  i2c_out(mbBusM, 0x42, PIN1, 1, (unsigned char *) &pin, 1);
  i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
  while(command)
  {
    i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
  } 

  while(1)
  {
    command = HIGH; pin = 26;
    i2c_out(mbBusM, 0x42, PIN1, 1, (unsigned char *) &pin, 1);
    i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    while(command)
    {
      i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    } 
    
    command = PAUSE; arg1 = 100;
    i2c_out(mbBusM, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
    i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    while(command)
    {
      i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    } 
    
    command = LOW; pin = 26;
    i2c_out(mbBusM, 0x42, PIN1, 1, (unsigned char *) &pin, 1);
    i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    while(command)
    {
      i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    } 
    
    command = PAUSE; arg1 = 100;
    i2c_out(mbBusM, 0x42, ARG1, PIN1, (unsigned char *) &arg1, 4);
    i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    while(command)
    {
      i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
    }
  }
}  
  

int main()
{  
  cog_run(i2cMaster, 512);
  
  mbBusS = i2cslave_open(10, 11, 0x42);
  
  while(1)
  {
    int command = 0;
    
    while(!command)
    {
      command = i2cslave_getReg(mbBusS, COMMAND);
    }
    int pin1 = (int) reg[PIN1];
    //int pin2 = (int) reg[PIN2];
    int state = (int) reg[STATE];
    int arg1, arg2, arg3, arg4, arg5;
    memcpy(&arg1, &reg[ARG1], 4);
    memcpy(&arg2, &reg[ARG2], 4);
    memcpy(&arg3, &reg[ARG3], 4);
    memcpy(&arg4, &reg[ARG4], 4);
    memcpy(&arg5, &reg[ARG5], 4);
    
    int retVal;
    
    switch(command)
    {
      case HIGH:
        high(pin1);
        break;
      case LOW:
        low(pin1);
        break;
      case INPUT:
        retVal = input(pin1);
        memcpy(&reg[RETVAL], &retVal, 4);
        break;
      case PAUSE:
        pause(arg1);
        break;
      case FREQOUT:
        freqout(pin1, arg1, arg2);
        break;
      case PULSOUT:
        pulse_out(pin1, arg1);
        break;
      case PULSIN:
        retVal = pulse_in(pin1, state);
        memcpy(&reg[RETVAL], &retVal, 4);
        break;
      case RCTIME:
        retVal = rc_time(pin1, state);
        memcpy(&reg[RETVAL], &retVal, 4);
        break;
    }
    i2cslave_putReg(mbBusS, 0, 0);
  }
}   
  
