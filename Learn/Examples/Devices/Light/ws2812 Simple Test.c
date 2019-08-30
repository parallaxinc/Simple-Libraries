/*
  ws2812 Simple Test.c
*/

#include "simpletools.h"                      // Library includes
#include "ws2812.h"

#define LED_PIN     13                        // led chain pin and count
#define LED_COUNT   4

ws2812 *leds;                                 // Set up ws2812 instance

int lightsA[] = { COLOR_RED, COLOR_YELLOW,    // 4-light pattern A
                  COLOR_GREEN, COLOR_BLUE }; 
int lightsB[] = { COLOR_YELLOW, COLOR_RED,    // 4-light pattern B
                  COLOR_BLUE, COLOR_GREEN };
void main()                                   // Main function
{
  leds = ws2812b_open();                      // Open leds instance
  
  int i = 0;                                  // Counting variable

  while(1)                                    // Main loop
  {
    i = (i + 1) % 2;                          // i counts 0, 1, 0, 1,...                                      
    
    print("i = %d\n", i);
    if(i == 0)                                // if i is 0
    {
      ws2812_set(leds, LED_PIN,               // Display pattern A
                     lightsA, LED_COUNT);      
    }                     
    else                                      // Otherwise...
    {
      ws2812_set(leds, LED_PIN,               // Display pattern B
                     lightsB, LED_COUNT);      
    }                     
    pause(100);                               // 0.1 s before repeat
  }      
}

