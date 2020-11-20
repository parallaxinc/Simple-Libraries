/*
  libdac2ch.c

  Test harness for dac2ch library.
*/

#include "simpletools.h"
#include "dac2ch.h"

dac2ch *dacA;
dac2ch *dacB;

int main()                                    
{
  // Start two DAC processes, one 8-bit and one 10 bit
  dacA = dac2ch_start(8);   
  dacB = dac2ch_start(10);   
  
  // Set P26 and P27 to 1.65 V, and P5 and P6 to 0.825 V.
  dac2ch_set(dacA, 26, 0, 128);
  dac2ch_set(dacB, 27, 0, 512);
  dac2ch_set(dacA, 5, 1, 64);
  dac2ch_set(dacB, 6, 1, 256);
  pause(3000);

  // Stop signals on P26 and P5 -> inputs
  dac2ch_set(dacA, 26, 0, -1);
  dac2ch_set(dacA, 5, 1, -1);
  pause(3000);

  // Swithc outputs that were on P27 and P6 to P26 and P5.
  dac2ch_set(dacB, 26, 0, 768);
  dac2ch_set(dacB, 5, 1, 192);
  pause(3000);
  
  // End the dac2ch processes
  dac2ch_stop(dacA);
  dac2ch_stop(dacB);
}  

