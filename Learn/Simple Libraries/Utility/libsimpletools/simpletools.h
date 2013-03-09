/**                                                                             
 * @file simpletools.h
 *
 * @author Andy Lindsay
 *
 * @version dev002 (see details for more info)
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2013. All Rights MIT Licensed.
 *
 * @brief WARNING, CONSTRUCTION ZONE: This is a preliminary library, 
 * major revisions pending, not for release.  This library provides 
 * convenience functions for:
 *
 * @li I/O control - convenient I/O pin monitoring and control functions
 * @li Timing - Delays, timeouts
 * @li Timed I/O - pulse generation/measurement, square waves, transition
 * counting, RC decay, etc.
 * @li Analog - D/A conversion, A/D conversation (but not yet), PWM, sine 
 * waves, etc.
 * @li Serial Communication - SPI, I2C, asynchronous
 * @li Memory - EEPROM (not yet), SD storage
 *
 * @details This (under development) library provides a set of
 * introductory functions that simplify monitoring, control and
 * communication with simple peripherals, including lights, buttons,
 * dials, motors, peripheral integrated circuits and prototyping with
 * simple systems that use pulse, or serial communication.  (A few
 * examples from the very large list of devices includes: servos,
 * ultrasonic distance sensors, accelerometers, serial liquid crystal,
 * display, etc.)
 *
 * Intended use: Accompanies introductory electronics, robotics and
 * programming lessons and projects on learn.parallax.com.  After
 * these lessons, bridge lessons will be added to familiarize the
 * programmer with standard practices used by the community for
 * adding libraries to support and endless variety of peripherals
 * and applications.
 */
 
#include <propeller.h>
#include <driver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cog.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sd.h>
#include <i2c.h>
#include <math.h>

// Global variables shared by functions in separate files
extern long iodt;
extern long t_timeout;
extern long pauseTicks;
extern long t_mark;
extern char setForget;
extern int fdserDriverIndex;
extern unsigned int buscnt;
extern int dacCtrBits;
 

// Values for use with SimpleIDE Terminal
#define HOME   1
#define CRSRXY 2
#define CRSRLF 3
#define CRSRRT 4
#define CRSRUP 5
#define CRSRDN 6
#define BEEP   7
#define BKSP   8
#define TAB    9
#define NL     10
#define CLREOL 11
#define CLRDN  12
#define CR     13
#define CRSRX  14
#define CRSRY  15
#define CLS    16

// Values for use with shift_in
#define   MSBPRE     0
#define   LSBPRE     1
#define   MSBPOST    2
#define   LSBPOST    3
  
// Values for use with shift_out
#define   LSBFIRST   0
#define   MSBFIRST   1

// Define types for simplified driver declarations
typedef FILE* serial;
typedef FILE* fdserial;
typedef FILE* sdcard;
typedef I2C* i2c;

/**
 * @brief Set an I/O pin to output-high
 *
 * @details This function set makes the Propeller
 * connect the I/O pin to its positive 3.3 V
 * supply voltage enabling it to source up to
 * 50 mA of current.
 *
 * @param pin Number of the I/O pin to set high
 */
void high(int pin);

/**
 * @brief Set an I/O pin to output-low
 *
 * @details This function makes the Propeller
 * connect the I/O pin to its ground 0 V
 * supply voltage enabling it to sink up to
 * 50 mA of current.
 *
 * @param pin Number of the I/O pin to set low
 */
void low(int pin);

/**
 * @brief Toggle the output state of the I/O pin.
 *
 * @details Change I/O pin's output state from low to high
 * or high to low.  This function assumes that some other
 * function has already set the I/O pin to output.
 *
 * @param pin I/O pin number
 *
 * @returns The new pin state
 */
unsigned int toggle(int pin);

/**
 * @brief Set an I/O pin to input
 *
 * @details This function makes the Propeller
 * connect the I/O pin to its input buffer
 * so that it can return the binary value of the
 * voltage applied by an external circuit.
 *
 * @param pin Number of the I/O pin to set to input
 *
 * @returns 1 or 0 to indicate high or low signal
 * received
 */
unsigned int input(int pin);

/**
 * @brief Reverse the direction of an I/O pin.
 *
 * @details If an I/O pin's direction is set to input, this
 * function changes it to output.  If it's set to output,
 * this function changes it to input.
 *
 * @param pin I/O pin number
 *
 * @returns The new pin direction.
 */
unsigned int reverse(int pin);

/**
 * @brief Check the state of an I/O pin without
 * setting it to input.
 *
 * @details Use this function instead of input if the
 * Propeller needs to maintain an output.  For example,
 * you can use this to monitor another cog's or counter's
 * output signal activity on a pin.  (Note: if the pin
 * is already set to input, it will return the state the
 * external circuit is applying, just like input.)
 *
 * @param pin Number of the I/O pin
 *
 * @returns The pin's state.  If the pin is an output,
 * 1 = 3.3 V and 0 = 0 V.  If the pin is an input,
 * 1 means V > 1.65 V, 0 means it's less.
 */
unsigned int get_state(int pin);

/**
 * @brief Check the direction of the I/O pin.                                        .
 *
 * @details This function will tell you the direction of the
 * I/O pin as seen by the cog executing it.  Keep in mind that
 * that your program might make other cogs use the I/O pin as
 * an output, and a cog that treats a pin as an output wins over
 * one that treats it as an input.
 *
 * @param pin I/O pin number
 *
 * @returns I/O pin direction as seen by the cog that runs the
 * function
 */
unsigned int get_direction(int pin);

/**
 * @brief Get I/O pin output state.
 *
 * @details Keep in mind that this function reports the value in the output
 * register for the cog running the function.  That doesn't tell you if the
 * I/O pin is set to input, or whether another cog is sending a different
 * output state.
 *
 * @param pin I/O pin number
 *
 * @returns ina register bit for I/O pin, either 1 or 0.
 */
unsigned int get_output(int pin);

/**
 * @brief Set an I/O pin to a given direction.                                        .
 *
 * @details This function sets an I/O pin to either output or input.
 *
 * @param pin I/O pin number
 * @param direction I/O pin direction
  */
void set_direction(int pin, int direction);

/**
 * @brief Set I/O pin output register bit to either 1 or 0.
 *
 * @details This function focuses on the I/O pins output register.  If you
 * intend to use it to send high or low signals, consider using high or low
 * instead.  This function can also be used in conjunction with setDirection
 * to send high or low signals.
 *
 * @param pin I/O pin to set high or low.
 * @param state 1 for high, 0 for low (when pin is actually set to output,
 * which can be done with setDirection.
 */
void set_output(int pin, int state);

/**
 * @brief Get states of a contiguous group of I/O pins
 *
 * @details This works the same as getState, but for a group of pins.  It
 * tells you the actual state of each pin, regardless of whether it's a 
 * voltage applied to intput or transmitted by an output.
 *
 * @param endPin the higest numbered pin.
 * @param startPin the lowest numbered pin.
 *
 * @returns states value containing the binary bit pattern.  The value for
 * startPin should be in bit-0, next in bit-1, etc.
 */
unsigned int get_states(int endPin, int startPin);

/**
 * @brief Get directions for a contiguous group of I/O pins
 *
 * @details Get direction register states from a contiguous group of bits 
 * in the cog's ouput register.
 *
 * @param endPin the higest numbered pin.
 * @param startPin the lowest numbered pin.
 *
 * @returns states Value containing a binary bit pattern.  The value for
 * startPin should be in bit-0, next in bit-1, etc.
 */
unsigned int get_directions(int endPin, int startPin);

/**
 * @brief Get output settings for a contiguous group of I/O pins
 *
 * @details Get output register settings for a contiguous group of bits 
 * in the cog's ouput register.
 *
 * @param endPin the higest numbered pin.
 * @param startPin the lowest numbered pin.
 *
 * @returns pattern Value containing a binary bit pattern.  The value 
 * for startPin should be in bit-0, next in bit-1, etc.
 */
unsigned int get_outputs(int endPin, int startPin);

/**
 * @brief Set directions for a contiguous group of I/O pins
 *
 * @details Set directions values in a contiguous group of bits in the 
 * cog's output register.
 *
 * @param endPin the higest numbered pin.
 * @param startPin the lowest numbered pin.
 * @param states value containing the binary bit pattern.  The value for
 * startPin should be in bit-0, next in bit-1, etc.
 */
void set_directions(int endPin, int startPin, unsigned int pattern);

/**
 * @brief Set output states for a contiguous group of I/O pins
 *
 * @details Set output states of a contiguous group of bits in the cog's
 * output register.
 *
 * @param endPin the higest numbered pin.
 * @param startPin the lowest numbered pin.
 * @param states value containing the binary bit pattern.  The value for
 * startPin should be in bit-0, next in bit-1, etc.
 */
void set_outputs(int endPin, int startPin, unsigned int pattern);

/**
 * @brief Delay cog from moving on to the next statement for a certain amount
 * of time.
 *
 * @details The defualt time increemnt is 1 ms, so pause(100) would delay for
 * 100 ms = 1/10th of a second.  This time increment can be changed with a call
 * to the setPauseDt function.
 *
 * @param dt The number of time increments to delay.
 */
void pause(int dt);

/**
 * @brief Delay cog from moving on to the next statement for a certain number
 * of system clock ticks.
 *
 * @details At 80 MHz, each clock tick is 12.5 ns.  Code overhead varies 
 * depending on memory model and optimization.  A simple test if you want a
 * certain number of clock ticks is:
 * 
 *  unsigned int ti, tf, us, pauseTicks;
 *  us = CLKFREQ/1000000;                               // 1 us worth of ticks
 *  pauseTicks = 10*us;                                 // 10 us of ticks
 *  ti = CNT;                                           // Save start time
 *  pause_ticks(pauseTicks);                            // Call pause_ticks
 *  tf = CNT;                                           // Save end time
 *  printf("pauseTicks = %d\n", pauseTicks);            // Display pauseTicks
 *  printf("delayTicks = %d\n", tf - ti);               // Display measured
 *
 * @param tticks the number of pause clock ticks.
 */
#define pause_ticks(pticks) __builtin_propeller_waitcnt(pticks+CNT, 0)

/**
 * @brief Mark the current time.
 *
 * @details The timeout function uses the marked time to determine if a timeout
 * has occurred.
 */
void mark(void);

/**
 * @brief Compares the time against the time elapsed since mark.
 *
 * @details The defualt time incremnt is 1 us, so timeout(2000) will return 1
 * if 2 ms or more has elapsed since mark, or 0 if it has not.
 *
 * @param time Number of time increments.
 */
int timeout(int time);

/**
 * @brief Waits a certain number of time increments from the last call to mark.
 *
 * @details The defualt time incremnt is 1 us, so wait(2000) will return wait
 * until 2 us after the last call to mark.  This function automatically updates
 * the marked time, so you can call it repeatedly without having to call mark.
 *
 * @param time Number of time increments.
 */
void wait(int time);

/**
 * @brief Set time increment for pause function
 *
 * @details Default time increment for pause function is 1 ms.  This function
 * allows you to change that delay to custom values. For example,
 * setPauseDt(CLKFREQ/2000) would set it to 1/2 ms increments.  To return to
 * default 1 ms increments, use setPauseDt(CLKFREQ/1000).
 *
 * @param clockticks the number of clock tics that pause(1) will delay.
 */
void set_pause_dt(int clockticks);

/**
 * @brief count number of low to high transitions an external input applies to
 * an I/O pin over a certain period of time.
 *
 * @param pin I/O pin number
 * @param duration Amount of time the measurement counts transitions
 *
 * @returns transitions The number of low to high transitions
 */
long count(int pin, long duration);

/**
 * @brief Set D/A voltge
 *
 * @details Uses duty modulation to generate a digital signal that can be fed to a low
 * pass RC filter for digital to analog voltage conversion.  Add an op amp buffer it
 * it needs to drive a load.  Also works well for LED brightness.
 *
 * Default resolution is 8-bits for output voltages ranging from 0 V to (255/256) of
 * 3.3 V.
 *
 * General equation is dacVal * (3.3 V/2^bits)
 *
 * Default is 8 bits, which results in dacVal * (3.3 V/ 256), so dacVal
 * specifies the number of 256ths of 3.3 V.  You can change the resolution with
 * the dac_ctr_res function.
 *
 * @param pin I/O pin number.
 * @param channel, use 0 or 1 to select the cog's CTRA or CTRB counter modules, that
 * are used for D/A conversion.
 * @param dacVal Number of 256ths of 3.3 V by default.  Use a value from 0 (0 V) 
 * to 255 .
 */
void dac_ctr(int pin, int channel, int dacVal);

/**
 * @brief Set D/A voltge resolution
 *
 * @details Uses duty modulation to generate a digital signal that can be fed to a low
 * pass RC filter for digital to analog voltage conversion.  Add an op amp buffer it
 * it needs to drive a load.  Also works well for LED brightness.
 *
 * Default resolution is 8-bits for output voltages ranging from 0 V to (255/256) of
 * 3.3 V.
 *
 * General equation is dacVal * (3.3 V/2^bits)
 *
 * Default is 8 bits, which results in dacVal * (3.3 V/ 256), so dacVal
 * specifies the number of 256ths of 3.3 V.
 *
 * @param pin I/O pin number
 * @param time Number of ms to maintain voltage
 * @param dacVal Numerator in fraction of 3.3 V.
 */
void dac_ctr_res(int bits);

/**
 * @brief Use an I/O pin to transmit PWM signal
 *
 * @details Typically used for signals that control DC motors.  Default
 * time increments are specified in 1 microsecond units.  Unit size can be changed
 * with a call to setIoDt funciton.
 *
 * @param tHigh time the output signal stays high
 * @param tCycle time of the cycle (high time + low time)
 */
void pwm(int tHigh, int tCycle);

/**
 * @brief Measure the duration of a pulse applied to an I/O pin
 *
 * @details Default time increments are specified in 1 microsecond units.  Unit size
 * can be changed with a call to setIoDt funciton.
 *
 * @param pin I/O pin number
 * @param state State of the pulse (1 for positive or high pulses, 0 for negative or
 * low pulses.
 *
 * @returns tPulse Number of time units the pulse lasted
 */
long pulse_in(int pin, int state);

/**
 * @brief Transmit a pulse with an I/O pin
 *
 * @details Default time increments are specified in 1 microsecond units.  Unit size
 * can be changed with a call to setIoDt funciton.  The pulse will be positive if the
 * I/O pin is transmitting a low signal before the call.  The pulse will be negative
 * if it transmits a high signal before the call.  When the pulse is done, the pin
 * returns to whatever state it was in before the pulse.  If the pin was an input, it
 * will be changed to output and use whatever value was in the output register bit
 * for the pin.  This defaults to low on startup, but you can pre-set it while leaving
 * the pin set to input with the setOutput function (or check it with getOutput).
 *
 * @param pin I/O pin number
 * @param time Amount of time the pulse lasts.
 */
void pulse_out(int pin, int time);

/**
 * @brief Set I/O pin to input and measure the time it takes a signal to transition from
 * a start state to the opposite state.
 *
 * @details Named rctime because because it is often used to measure a resistor-capacitor
 * circuit's tendency to "decay" to either ground or 5 V (depending on wiring).  Default
 * time increments are specified in 1 microsecond units.  Unit size can be changed with a
 * call to setIoDt funciton.  The pulse will be positive if the I/O pin is transmitting a
 * low signal before the call.
 *
 * @param pin I/O pin number
 * @param state Starting pin state
 *
 * @returns time from starting pin
 */
long rc_time(int pin, int state);

/**
 * @brief Make an I/O pin transmit a repeated high/low signal at a certain frqeuency.
 *
 * @details Frequency can range from 1 Hz to 128 MHz.  High and low times are the same.
 * Positive time values will make the library use the same cog that is executing
 * your code generate the square wave and wait for it to finish.  Negative time
 * values will caluse the library to launch the process into another cog and
 * return immediately.
 *
 * @param pin I/O pin that transmits square wave fequency
 * @param time Time to transmit square wave (in ms)
 * @param frequency Square wave frequency
 *
 */
void square_wave(int pin, int time, int freq);

/**
 * @brief Sets the timeout value for the following timed I/O functions: pulseIn, rcTime
 *
 * @details Time increment is set in clock ticks.  For example, the default of 0.25
 * seconds is set with setTimeout(CLKFREQ/4).  To set the timeout to 20 ms, you could
 * use setTimeout(CLKFREQ/50).
 *
 * @param clockTics Number of clock ticks for timed I/o
 */
void set_io_timeout(long clockTicks);

/**
 * @brief Sets the time increment for the following timed I/O functions: count, pulsin,
 * pulseout, rctime.
 *
 * @details Time increment is set in clock ticks.  For example, the default of 1 us
 * units is specified with setDt(CLKFREQ/1000000).  For 2 microsecond units, use
 * setDt(CLKFREQ/500000).
 *
 * @param clockTics Number of clocktics that represents one I/O time increment.
 */
void set_io_dt(long clockTicks);


/**
 * @brief Receive data from a synchronous serial device
 *
 * @param pinDat Data pin
 * @param pinClk Clock pin
 * @param mode Mode
 * @param bits number of binary values to transfer
 *
 * @returns value received from the synchronous serial device.
 */
int shift_in(int pinDat, int pinClk, int mode, int bits);

/**
 * @brief Send data to a synchronous serial device
 *
 * @details (not implemented yet)
 *
 * @param dataPin Data pin
 * @param clockPin Clock pin
 * @param mode Mode
 * @param bits number of binary values to transfer
 * @param value to transmit
 */
void shift_out(int pinDat, int pinClk, int mode, int bits, int value);

/**
 * @brief Set up a simple serial driver with transmit & receive pins.
 *
 * @param pinTxOut transmitting output pin.
 *
 * @param pinRxIn receiving input pin.
 *
 * @param baud rate in bits per second.
 *
 * @returns a file pointer that you can pass to functions like fptrintf.
 */
FILE* sser_setTxRx(int pinTxOut, int pinRxIn, int baudRate);

/**
 * @brief Set up a simple serial driver with just a transmit pin.
 *
 * @details Example:
 *
 *   serial lcd = sser_setTx(11, 9600);    // Serial driver transmits on P11
 *   fputc(22, LCD);                       // Transmit 22
 *   fputc(12, lcd);                       // Transmit 12 
 *   pause(5);                             // Wait 5 ms
 *   fptrintf(lcd, "Hello!!!");            // Transmit a string
 *
 * @param pinTxOut transmitting output pin.
 *
 * @param baud rate in bits per second.
 *
 * @returns a file pointer that you can pass to functions like fptrintf.
 */
FILE* sser_setTx(int pinTxOut, int baudRate);

/**
 * @brief Set up a simple serial driver with just a receive pin.
 *
 * @param pinTxOut transmitting output pin.
 *
 * @param baud rate in bits per second.
 *
 * @returns a file pointer that you can pass to functions like fptrintf.
 */
FILE* sser_setRx(int pinRxIn, int baudRate);

/**
 * @brief Close a simple serial deiver.
 *
 * @param peripheral the name of the simple serial deiver's file pointer.
 */
int sser_close(FILE* peripheral);

/**
 * @brief Set up a full duplex serial driver.
 *
 * @param pinTxOut transmitting output pin.
 *
 * @param pinRxIN receiving input pin.
 *
 * @param baud rate in bits per second.
 *
 * @returns a file pointer that you can pass to functions like fptrintf.
 */
FILE* fdser_start(int pinTxOut, int pinRxIn, int baudRate, int mode);

/**
 * @brief Stop the serial deiver.
 *
 * @param peripheral the file pointer fdser_start returned.
 */
int fdser_stop(FILE* peripheral);

/**
 * @brief mount an SD card with the minimal 4-pin interface.
 *
 * @param doPin the SD card's data out pin.
 *
 * @param clkPin the SD card's clock pin.
 *
 * @param diPin the SD card's data in pin.
 *
 * @param csPin the SD card's chip select pin.
 *
 * @returns status 0 if successful, or an error code.
 */
int sd_mount(int doPin, int clkPin, int diPin, int csPin);


/**
 * @brief Set up an I2C bus.
 *
 * @detail After you have set up the bus, you can use i2cread and i2cwrite functions 
 * in propgcc\propeller-elf\include\i2c.h to communicate on the bus.
 *
 * @param sclpin the I2C bus' serial clock pin.
 *
 * @param sdapin the I2C bus' serial data pin.
 *
 * @returns a pointer to the I2C bus.  You will need this to pass to the i2cWrite and
 * i2cRead functions for communicaiton on the bus. 
 */
I2C* i2c_newbus(int sclpin, int sdapin);

/**
 * @brief Convert value to zero terminated text string
 *
 * @details Given an int, a character array pointer and a base, this function
 *          converts the int into the characters that represent the value in
 *          the specified base.
 *
 * @param   i an integer value
 * @param   b[] a character array pointer
 * @param   base the number base for the character representation
 *
 * @returns the character array address it received.
 */
char* itoa(int i, char b[], int base);

int add_driver(_Driver *driverAddr);

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




