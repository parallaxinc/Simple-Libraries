/*
  Seven Segment.c
  
  Display digits on a 7 segment (common cathode) LED display.
  
  http://learn.parallax.com/propeller-c-simple-circuits/seven-segment-display
*/

#include "simpletools.h"                      // Include simpletools

int main()                                    // main function
{
  set_directions(15, 8, 0b11111111);          // P15...P8 -> output
                                              
  set_outputs(15, 8, 0b11100111);             // 0 -> 7-segment display
  pause(500);
  set_outputs(15, 8, 0b10000100);             // 1
  pause(500);
  set_outputs(15, 8, 0b11010011);             // 2
  pause(500);
  set_outputs(15, 8, 0b11010110);             // 3
  pause(500);
  set_outputs(15, 8, 0b10110100);             // 4
  pause(500);
  set_outputs(15, 8, 0b01110110);             // 5
  pause(500);
  set_outputs(15, 8, 0b01110111);             // 6
  pause(500);
  set_outputs(15, 8, 0b11000100);             // 7
  pause(500);
  set_outputs(15, 8, 0b11110111);             // 8
  pause(500);
  set_outputs(15, 8, 0b11110110);             // 9
  pause(500);
}
