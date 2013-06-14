/*
  Seven Segment with Array.c
  
  Access an array for displaying digits on a 7 segment (common cathode) 
  LED display.  Note, itoa call will probably be replaced with
  bin2str(n[i], 8) where n[i] is a number, and 8 is the number of binary 
  digits to display.  At that point, the s[] array declaration will not be
  necessary.  bin2str has not yet been added to simpletools.  
  
  http://learn.parallax.com/propeller-c-simple-circuits/seven-segment-display
*/
#include "simpletools.h"                      // Include simpletools

// Declare array of binary patterns for 7-segment LED digits 0...9.
int n[] = {0b11100111, 0b10000100, 0b11010011, 0b10110100, 0b10110100, 
           0b01110110, 0b01110111, 0b11000100, 0b11110111, 0b11110110};

char s[9];                                    // binary display string 

int main()                                    // main function
{
  set_directions(15, 8, 0b11111111);          // P15...P8 -> output
  pause(1000);                                // Wait 1 s for terminal app

  for(int i = 0; i < 10; i++)                 // Count 0...9
  {
    set_outputs(15, 8, n[i]);                 // n[i] -> 7 segment
    print("n[%d] = %08b\n", i, n[i]);         // Display n[i] in binary
               
    pause(1000);                              // Wait 1 s.
  }
}
