/*
  ws2812 Demo.c
*/

#include "simpletools.h"
#include "ws2812.h"

// led chain
#define LED_PIN     13
#define LED_COUNT   4

// 4 Parallax WS2812B Fun Boards
uint32_t ledColors[LED_COUNT];

// LED driver state
ws2812 *driver;

// pattern for chase
uint32_t pattern[] = {
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW, 
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_INDIGO
};

#define pattern_count  (sizeof(pattern) / sizeof(pattern[0]))

// forward declarations
void alternate(int count, int delay);
void chase(int count, int delay);
void pause(int ms);

int main(void)
{
    // load the LED driver
    if (!(driver = ws2812b_open()))
        return 1;
        
    // repeat the patterns
    for (;;) {
    
        // alternate inner and outer colors
        alternate(8, 500);
        
        // chase
        chase(32, 200);
    }
    
    // close the driver
    ws2812_close(driver);
           
    return 0;
}

void alternate(int count, int delay)
{
    // start with the outer two LEDs green and the inner two red
    ledColors[0] = COLOR_GREEN;
    ledColors[1] = COLOR_RED;
    ledColors[2] = COLOR_RED;
    ledColors[3] = COLOR_GREEN;

    // repeat count times or forever if count < 0
    while (count < 0 || --count >= 0) {
    
        // swap the inner and outer colors
        ledColors[0] = ledColors[1];
        ledColors[1] = ledColors[3];
        ledColors[2] = ledColors[3];
        ledColors[3] = ledColors[0];
    
        // Set LEDs in the chain
        ws2812_set(driver, LED_PIN, ledColors, LED_COUNT);
            
        // delay between frames
        pause(delay);
    }
}

// the chase effect was translated from Spin code by Jon McPhalen
void chase(int count, int delay)
{
    int base = 0;
    int idx, i;
    
    // repeat count times or forever if count < 0
    while (count < 0 || --count >= 0) {
    
        // fill the chain with the pattern
        idx = base;                             // start at base
        for (i = 0; i < LED_COUNT; ++i) {       // loop through connected leds
            ledColors[i] = pattern[idx];        // Set channel color
            if (++idx >= pattern_count)         // past end of list?
                idx = 0;                        // yes, reset
        }
        if (++base >= pattern_count)            // set the base for the next time
            base = 0;
    
        // set LEDs in the chain
        ws2812_set(driver, LED_PIN, ledColors, LED_COUNT);
            
        // delay between frames
        pause(delay);
    }
}

