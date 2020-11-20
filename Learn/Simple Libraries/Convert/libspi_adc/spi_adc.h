/* 
* spi_adc.h
* Use Serial Peripheral Interface to communicate with
* an MCP3x02 to measure voltage across channels 0 and 1 to ground.
* 
* Don't forget to double check your hardware, and post problems
* on the Parallax forums! 
* 
* Written by Andrew Enright
*/
#include "simpletools.h"

/* Function MCP3X02_getVolts gets a measurement from a SPI ADC.
* spi_adc can be called directly if you know how many bits your ADC is, 
* or you can call one of the MCP3x02 (3202 or 3002) cover methods
* that tell you how many bits it is. 
* PARAMETERS:
* ch      = Channel, either 0 or 1 (anything but a zero will return measures from channel 1)
* mosi    = Master Out, Slave In
* miso    = Master In, Slave Out
* clk     = bus clock
* cs_adc  = ADC Chip Select, active low (leave high when not in use)
* vref    = reference voltage, 2.7-5.5V. Recommend measuring with voltmeter for best results.
* 
*  RETURN: Returns a floating-point value which is the voltage on the MCP3002, which should be
*  somewhere between GND and VREF.
*         Returns -1.0 if MOSI, MISO, CLK, CS, or VREF are -1 (happens when not initialized).  
*/

float MCP3202_getVolts(int ch, int mosi, int miso, int clk, int csin, float vref);

float MCP3002_getVolts(int ch, int mosi, int miso, int clk, int csin, float vref);

float spi_adc(int ch, int mosi, int miso, int clk, int csin, float vref, int bits);
