/* spi_adc.c
* Use Serial Peripheral Interface to communicate with
* an MCP3202 to measure voltage across channels 0 and 1 to ground.
* 
* Don't forget to double check your hardware, and post problems
* on the Parallax forums! 
* 
* Written by Andrew Enright
*/
#include "spi_adc.h" // Include MCP3002.h, which includes simpletools.h
#include "simpletools.h"

//int MCP3002_init(int mosi, int miso, int clk, int csin, float vref)
//float MCP3002_getVolts(int ch);



float MCP3202_getVolts(int ch, int mosi, int miso, int clk, int csin, float vref) {
  return spi_adc(ch,mosi,miso,clk,csin,vref,12);  
} 

float MCP3002_getVolts(int ch, int mosi, int miso, int clk, int csin, float vref) {
  return spi_adc(ch,mosi,miso,clk,csin,vref,10);  
} 

float spi_adc(int ch, int mosi, int miso, int clk, int csin, float vref, int bits) {
    if (vref < 0) {
   print("Error! Float Vref = %f, should not be <= 0\n", vref);
  } else {
        short bitsIn = 0b0000000000000000;
        int CS_ADC=csin, SCK=clk, MISO=miso, MOSI=mosi; // DO = MOSI, DI = MISO
        float VREF = vref;
        high(CS_ADC);
        low(CS_ADC); // CS_ADC low selects chip
        //boot sequence: start, sgl/diff (1 for single-ended mode), odd/sign (channel in single-ended mode), msbf
        if (ch == 0){
          shift_out(MOSI, SCK, MSBFIRST, 4, 0b1101); // Send "read channel 0 single-ended"
        } else {
          shift_out(MOSI, SCK, MSBFIRST, 4, 0b1111); // Send "read channel 1 single-ended"
        } 
        bitsIn = shift_in(MISO,SCK,MSBPOST,bits);
        float volts = bitsIn * VREF / (pow(2,bits)); // 1024: 2^10, it's a 10-bit ADC after all.
        high(CS_ADC);
        usleep(5);
        shift_out(MOSI, SCK, MSBFIRST, 1, 0b1);
        return volts;
    }
  return -99.99;  
} 

