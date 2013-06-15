/*
  Hello VGA.c
  Test Propeller VGA.  P8-V, P9-H, P10-B0, P11-B1, P12-G0, P13-G1
                       P14-R0, P15-R1. 
*/

#include "simpletools.h"                      // Include simple tools
#include "vgatext.h"                          // Include VGA text

int main()                                    // Main function
{
  vga_text_start(8);                          // P8 basepin to V
  vga_text_str("Hello Propeller VGA!");       // Display hello message
  while(1);                                   // This cog keeps going
}


