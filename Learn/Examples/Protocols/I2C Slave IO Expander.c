/*
  I2C Slave IO Expander.side                 //                               //
  
  Propeller firmware mockup as I2C slave I/O expander.
*/

#include "simpletools.h"                     // Library includes
#include "simplei2c.h"
#include "i2cslave.h"

#define COMMAND 0                            // I2C Slave register offsets
#define PIN1 1
#define PIN2 2
#define STATE 3
#define ARG1 4
#define ARG2 8
#define ARG3 12
#define ARG4 16
#define ARG5 20
#define RETVAL 24

#define HIGH 1                               // Command codes
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
// #define COUNT 12
#define FREQOUT 13
#define RCTIME 16

// #define SHIFTIN 17
// #define SHIFOUT 18
// #define SEROUT 19
// #define SERIN 20

// #define SERVO_ANGLE 24
// #define SERVO_SPEED 25
// #define SERVO_SET 26
// #define SERVO_SETRAMP 27

// #define PING_US_ECHO 28
// #define PING_CM 29
// #define PING_IN 30


i2c *mbBusM;                                  // I2C master bus process ID
i2cslave *mbBusS;                             // I2C slave bus process ID

static char *reg;                             // I2C slave register 0 


int i2cMasterCom();
void i2cMaster();                              // I2C master for other cog

int main()
{  
  // The I2C master code is run in another cog so that it has a separate processor
  // that's signalling the bus.  
  cog_run(i2cMaster, 512);                     // Run I2C master in separate cog
  
  // The I2C slave processor converts incoming I2C signals to read/writes to 32 
  // byte "registers".  It runs in a separate cog, but this cog will monitor the
  // registers.
  mbBusS = i2cslave_open(10, 11, 0x42);        // Run I2C slave processor (separate cog)

  // This is the address of the 0th element in a 32 byte array of registers that
  // can be read from or written to in the I2C slave device.
  reg = i2cslave_regAddr(mbBusS);              // Get I2C slave memory address

  while(1)                                     // Main I2C slave processing loop
  {
    int command = 0;                           // Make sure command register is 0
    
    // Wait for I2C master to change value of command register to a command value.
    // A requirement of this particulare I2C slave device is that all other registers
    // that the command will need receive values before the command.
    while(!command)              
    {
      command = i2cslave_getReg(mbBusS, COMMAND);
    }
    
    // After command becomes nonzero, get the other register values..
    int pin1 = (int) reg[PIN1];
    int pin2 = (int) reg[PIN2];
    int state = (int) reg[STATE];
    int arg1, arg2, arg3, arg4, arg5;
    int retVal = 0;
    
    memcpy(&arg1, &reg[ARG1], 4);
    memcpy(&arg2, &reg[ARG2], 4);
    memcpy(&arg3, &reg[ARG3], 4);
    memcpy(&arg4, &reg[ARG4], 4);
    memcpy(&arg5, &reg[ARG5], 4);
    
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
    //print("i:%d, ", i++);
    //for(int n = 0; n < 32; n++) print("%d:%d, ", n, reg[n]);
    //print("\n");
    //pause(100);
    i2cslave_putReg(mbBusS, 0, 0);
  }
}   
  
int i2cMasterCom()
{
  int command = -1, pin1 = -1, pin2 = -1, state = -1;
  int arg1 = -1, arg2 = -1, arg3 = -1, arg4 = -1, arg5 = -1;
  int retValList[] = {INPUT, GETDIR, GETOUTPUT, PULSIN, RCTIME};
  int hasRetVal = 0;
  int retVal = 0;

  for(int n = 0; n < sizeof(retValList); n++)
  {
    if(command == retValList[n]) hasRetVal = 1;
  }    
  if(arg5 > -1) i2c_out(mbBusM, 0x42, ARG5, 1, (unsigned char *) &arg5, 4);
  if(arg4 > -1) i2c_out(mbBusM, 0x42, ARG4, 1, (unsigned char *) &arg4, 4);
  if(arg3 > -1) i2c_out(mbBusM, 0x42, ARG3, 1, (unsigned char *) &arg3, 4);
  if(arg2 > -1) i2c_out(mbBusM, 0x42, ARG2, 1, (unsigned char *) &arg2, 4);
  if(arg1 > -1) i2c_out(mbBusM, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
  if(arg1 > -1) i2c_out(mbBusM, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
  if(state > -1) i2c_out(mbBusM, 0x42, STATE, 1, (unsigned char *) &state, 1);                      
  if(pin2 > -1) i2c_out(mbBusM, 0x42, PIN2, 1, (unsigned char *) &pin2, 1);                      
  if(pin1 > -1) i2c_out(mbBusM, 0x42, PIN1, 1, (unsigned char *) &pin1, 1);                      
  if(command > 0) i2c_out(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
  while(command)
  {
    i2c_in(mbBusM, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
  } 
  if(hasRetVal)
  {
    i2c_in(mbBusM, 0x42, RETVAL, 1, (unsigned char *) &retVal, 4);
  }    
  command = 0, pin1 = -1, pin2 = -1, state = -1;
  arg1 = -1, arg2 = -1, arg3 = -1, arg4 = -1, arg5 = -1;
  return retVal;
}  
  

void i2cMaster()                              // I2C master for other cog
{
  char command, pin;
  int arg1, arg2, pinState;
  
  mbBusM = i2c_newbus(8,  9,   0);            // Start I2C master

  pause(100);
  
  command = FREQOUT; pin = 4; arg1 = 2000; arg2 = 3000; i2cMasterCom();

  while(1)
  {
    command = INPUT; pin = 5;
    pinState = i2cMasterCom();

    command = LOW;
    if(pinState) command = HIGH;
    pin = 27;
    i2cMasterCom();
    
    command = HIGH; pin = 26; i2cMasterCom();
    
    command = PAUSE; arg1 = 100;  i2cMasterCom();
    
    command = LOW; pin = 26;  i2cMasterCom();
    
    command = PAUSE; arg1 = 100; i2cMasterCom();
  }
}  
  

