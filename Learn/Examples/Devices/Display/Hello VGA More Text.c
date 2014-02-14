/*
  Hello VGA.c
  
  Test some of the vgatext library's features with a VGA dispaly.

  http://learn.parallax.com/propeller-c-simple-devices/vga-text-display
*/

#include "simpletools.h"                      // Library includes
#include "vgatext.h"

vgatext *vga;                                 // VGA identifier

int main(void)                                // Main function
{
  vga = vgatext_open(0);                      // Open VGA port with P8 base
    
  dprint(vga,"Hello VGA.\n");                 // Message + newline
  dprint(vga,"Hello again!\n");               // Another message

  for(int n = 3; n < 7; n ++)                 // Loop with n from 3 to 7
  {
    vgatext_setXY(2 * n - 3, n);              // Cursor positions with n
    dprint(vga, "*<-(x=%d, y=%d)", 2*n-3, n); // Astereisk + coordinates
  }

  dprint(vga,"\n\nPalettes: ");               // Palettes text
  int palette;                                
  for(palette = 7; palette >= 0; palette --)  // Loop palettes from 0 to 7
  {
    vgatext_setColors(palette);               // Set palette
    dprint(vga, "%d", palette);               // Digit with its palette
  }
    
  dprint(vga,"\n\nAll Done");                 // Last message
}

