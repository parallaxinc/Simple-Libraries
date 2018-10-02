/*
  I2C Slave IO Expander.c
  
  Propeller I2C master running in one cog controlling/monitoring an I2C slave I/O expander 
  that's running in another cog.  All the control/monitoring info is exchanged between
  cogs through an I2C bus.  The I2C slave uses a second cog to allow I2C messages 
  to automatically store/retrieve values to/from registers.
  
  Test circuit:
   - Connect 10 k resistor to 3.3 V and breadboard row (sclk pull-up)
   - Connect a second 10 k pull-up resistor to 3.3 V and a different breadboard row (sda pull-up)
   - jumper master sclk P8 to sklk pull-up breadboard row
   - jumper master sda P9 to sda pull-up breadboard row
   - jumper slave sclk P10 to sklk pull-up breadboard row
   - jumper slave sda P11 to sda pull-up breadboard row
   - P4 to piezo speaker +
   - piezo speaker - to GND
   - P5 to bottom terminal of a pushbutton through 220 ohms.
   - 10 k resistor from GND to bottom terminal of pushbutton
   - jumper from top terminal of pushbutton to 3.3 V.
   - P26 to LED circuit to GND (built into Propeller Activity Board and Flip)
   
  The I2C master sends the I2C slave commands to make it make the piezo speaker beep for 2 s 
  at 3 kHz.  After that, the I2C master code goes into a loop that makes the I2C slave check 
  the P5 pushbutton repeatedly.  While the P5 pushbutton is pressed and held, the I2C master 
  makes I2C slave blink the P26 LED light rapidly, with 50 ms pauses after each high/low state 
  change.  

*/

#include "simpletools.h"                      // Library includes
#include "simplei2c.h"
#include "i2cslave.h"

#define COMMAND 0                             // I2C Slave register indexes
#define PIN1 1
#define PIN2 2
#define STATE 3
#define ARG1 4
#define ARG2 8
#define ARG3 12
#define ARG4 16
#define ARG5 20
#define RETVAL 24

#define HIGH 1                                // Command codes
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


i2c *i2cBusMaster;                            // I2C master bus process ID
i2cslave *i2cBusSlave;                        // I2C slave bus process ID

static char *reg;                             // I2C slave register 0 


int i2cMasterCom();
void i2cMaster();                             // I2C master for other cog

int main()
{  
  // The I2C master code is run in another cog so that it has a separate processor
  // that's signaling the bus.  
  cog_run(i2cMaster, 512);                     // Run I2C master in separate cog
  
  // The rest of the main function focuses on how to interact with the I2C bus 
  // as an I2C slave device.
  
  // The I2C slave processor converts incoming I2C messages addressed to the target
  // device (address 0x42 in this case) and reads/writes to 32 byte "registers".  It 
  // runs in a separate cog, and this cog will monitor changes made to the registers.
  i2cBusSlave = i2cslave_open(10, 11, 0x42);        // Run I2C slave processor (separate cog)

  // This copies the Propeller memory address of the 0th element in the 32 byte array 
  // of registers that can be read from or written to in the I2C slave device.
  reg = i2cslave_regAddr(i2cBusSlave);              // Get I2C slave memory address

  // This particular I2C device is designed to allow all the details of the command
  // to be set up first.  In other words, any values in the PIN1, PIN2, STATE, and 
  // ARG1 through ARG5 registers that pertain to the command have to be set first
  // Then, as soon as the command byte becomes nonzero, this main loop executes the 
  // command (and its arguments).

  while(1)                                     // Main I2C slave processing loop
  {
    int command = 0;                           // Make sure command register is 0
    
    // Wait for I2C master to change value of the command register to a nonzero 
    // value.  Again, a requirement of this particular I2C slave device is that all 
    // other registers that the command will need receive values before the command 
    // value is set.
    while(!command)
    {
      command = i2cslave_getReg(i2cBusSlave, COMMAND);
    }
    
    // Remember that the all the i2C registers already have values, and remember also
    // that reg stores the starting address of the 32 I2C slave device's registers.  
    // So, instead of calling a function to get all the register values, they are just 
    // copied from &reg[INDEX]. 

    // After command becomes nonzero, get the other register values and copy them 
    // to variables.  Then, execute the command.  
    
    // Copy register contents to variables.
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
    
    // Execute the command.  This switch statement uses function calls built
    // into the simpletools library.
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
    
    // Display register contents.
    // print("i:%d, ", i++);
    // for(int n = 0; n < 32; n++) print("%d:%d, ", n, reg[n]);
    // print("\n");
    // pause(100);
    
    // Clear the command register.  Since this is the last step, the
    // I2C master can poll this I2C slave device command register to find out 
    // when it is finished with one command and ready for the next.
    i2cslave_putReg(i2cBusSlave, 0, 0);
  }
}   
  

// The i2cMaster function is what gets launched into another cog.  From there
// it communicates with the I2C slave cog through the I2C bus.  i2cMaster contains
// a higher level loop.  After each command is set up, i2cMasterCom is called 
// to deal with sending the values, polling the device for when its command
// register returns to zero, and returning result values for certain commands.   


// Variables that i2cMaster and i2cMasterCom share.  Yes, these could also be
// exchanged as parameters.
int command = -1, pin1 = -1, pin2 = -1, state = -1;
int arg1 = -1, arg2 = -1, arg3 = -1, arg4 = -1, arg5 = -1;
int retValList[] = { INPUT, GETDIR, GETOUTPUT, PULSIN, RCTIME };
int hasRetVal = 0;
int retVal = 0;
int pinState = 0;

void i2cMaster()                              // I2C master for other cog
{
  i2cBusMaster = i2c_newbus(8,  9,   0);      // Start I2C master bus
  
  // Wait for the I2C slave bus to start.
  pause(1);                                 

  // Send a speaker tone.  The speaker uses one pin (pin1 register) and two 
  // arguments -ms duration to arg1 and Hz frequency to arg2.  Keep in mind that
  // even though the command variable is set first here, the i2cMasterCom transmits
  // it last.  Again, that's because the I2C slave device starts executing a command
  // as soon as its command register changes to a nonzero value.  That's why all the
  // other registers are set first.  The i2cMasterCom function also polls until the
  // command register becomes zero before returning.
  command = FREQOUT; pin1 = 4; arg1 = 2000; arg2 = 3000; i2cMasterCom();

  // The main loop sends the I2C slave commands to make it check a pushbutton connected
  // to P5.  When P5 is high (button pressed), it sends commands that make the slave 
  // device blink a light.  
  while(1)
  {
    // Set command to INPUT and pin1 to 5.  Then, call i2cMasterCom and copy the value
    // it returns to a variable named pinState.
    command = INPUT; pin1 = 5;
    pinState = i2cMasterCom();

    // If the pushbutton is being held down, blink the light with high low and pause
    // commands, sent to the slave cog over the I2C bus.  Only the arguments required by
    // a given command need to be set to values.
    if(pinState)
    {
      command = HIGH; pin1 = 26; i2cMasterCom();
    
      command = PAUSE; arg1 = 50;  i2cMasterCom();
    
      command = LOW; pin1 = 26;  i2cMasterCom();
    
      command = PAUSE; arg1 = 50; i2cMasterCom();
    }      
  }
}  
  

// The i2cMasterCom function parses a given command and only transmits the
// arguments that each command needs to make the I2C slave device do its job.
// Since the slave device's design waits for its command register to become
// nonzero before executing a value, the command value is transmitted last.

// For more info on how i2c_out works, try these two resources:
// (1)
// http://learn.parallax.com/tutorials/language/propeller-c/propeller-c-simple-protocols/diy-i2c  
// (2)
// Open SimpleIDE Help -> Simple Library Reference, then click simplei2c.h

int i2cMasterCom()
{
  // This sequence transmits values of variables that are not -1 via I2C.  Each i2c_out
  // call has to have: the name of the bus returned by i2c_newbus, the I2C slave device's
  // address, the register address within the i2c slave device (0..31), the number of bytes
  // in that address, a pointer to a byte array containing the one or more bytes of data
  // to be transferred to the I2C slave device's registers, and the number of bytes to transmit.
  if(arg5 > -1) i2c_out(i2cBusMaster, 0x42, ARG5, 1, (unsigned char *) &arg5, 4);
  if(arg4 > -1) i2c_out(i2cBusMaster, 0x42, ARG4, 1, (unsigned char *) &arg4, 4);
  if(arg3 > -1) i2c_out(i2cBusMaster, 0x42, ARG3, 1, (unsigned char *) &arg3, 4);
  if(arg2 > -1) i2c_out(i2cBusMaster, 0x42, ARG2, 1, (unsigned char *) &arg2, 4);
  if(arg1 > -1) i2c_out(i2cBusMaster, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
  if(arg1 > -1) i2c_out(i2cBusMaster, 0x42, ARG1, 1, (unsigned char *) &arg1, 4);
  if(state > -1) i2c_out(i2cBusMaster, 0x42, STATE, 1, (unsigned char *) &state, 1);                      
  if(pin2 > -1) i2c_out(i2cBusMaster, 0x42, PIN2, 1, (unsigned char *) &pin2, 1);                      
  if(pin1 > -1) i2c_out(i2cBusMaster, 0x42, PIN1, 1, (unsigned char *) &pin1, 1);                      

  // Make sure to send the command last, after all the other values have been sent.
  if(command > 0) i2c_out(i2cBusMaster, 0x42, COMMAND, 1, (unsigned char *) &command, 1);

  // When slave device has finished executing the command, the command register will return
  // to zero.  This loop polls the command register until that happens before sending the 
  // next command.
  while(command)
  {
    i2c_in(i2cBusMaster, 0x42, COMMAND, 1, (unsigned char *) &command, 1);
  } 

  // This loop checks the retValList array for command values that expect a
  // return value.  If a match is found, it retrieves the return value with an 
  // i2c_in call, which writes the four byte return value to retVal, an int 
  // variable.
  for(int n = 0; n < sizeof(retValList); n++)
  {
    if(command == retValList[n])
    {
      i2c_in(i2cBusMaster, 0x42, RETVAL, 1, (unsigned char *) &retVal, 4);
      break;
    }      
  } 
  
  // Set all the variables to their "do not transmit" state.  The i2cMaster function
  // will change the values it wants sent before calling this function again.  This
  // ensures that no extraneous values are transmitted, which in turn reduces message
  // time.
  command = 0, pin1 = -1, pin2 = -1, state = -1;
  arg1 = -1, arg2 = -1, arg3 = -1, arg4 = -1, arg5 = -1;
  
  // Return a value.  0 for success of non-return value commands, or the value in the
  // case of commands with a return value.
  return retVal;
}  

