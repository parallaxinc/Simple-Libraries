/* Measure Volts
* Use Serial Peripheral Interface to communicate with
  an MCP3202 to measure voltage across channels 0 and 1 to ground.
* 
* Don't forget to double check your hardware, and post problems
* on the Parallax forums! 
* 
* Written by Andrew Enright
*/
#include "spi_adc.h" // Include simpletools lib 
#include "simpletools.h"
int t_CS=26, t_clk=23, t_miso=24, t_mosi=25; // DO = MOSI, DI = MISO
float t_vref = 5.08;

int main() // Main function
{  
      while(1) // Main loop
      {
        putchar(CLS); //clear screen between updates
        float v0 = MCP3202_getVolts(0, t_mosi, t_miso, t_clk, t_CS, t_vref);
        float v1 = MCP3202_getVolts(1, t_mosi, t_miso, t_clk, t_CS, t_vref);
        print("%cCh0: %f V\nCh1: %f V\n", HOME,v0, v1);
        pause(500); // Wait 0.5 s before repeat
      }//end while    
} //end main
