/*
  Hello VGA.c
  
  Test some of the vgatext library's features with a VGA display.

  http://learn.parallax.com/propeller-c-simple-devices/vga-text-display
*/

#include "simpletools.h"                      // Library includes
#include "vgatext.h"

vgatext *vga;                                 // VGA identifier

int main(void)                                // Main function
{
  vga = vgatext_open(0);                      // Open VGA port with P0 base
    
  dprint(vga,"Hello VGA.\n");                 // Message + newline
  dprint(vga,"Hello again!\n");               // Another message

  vgatext_setXY(3, 4);                        // Set position
  vgatext_setColors(5);                       // Set color palette

  dprint(vga, "* <- x=3 y=4 color=5");        // Text at position in palette
}

