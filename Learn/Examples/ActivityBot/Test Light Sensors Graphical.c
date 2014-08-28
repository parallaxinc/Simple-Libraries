/*
  Test Light Sensors Graphical.c

  http://learn.parallax.com/activitybot/using-measurements
*/

#include "simpletools.h"


int lightLeft, lightRight, ndiff, position;

int main()                    
{
  print("lightLeft   lightRight  ndiff\n\n\n\n");
  print("|------------------------|------------------------|\n");              
  print("-100                     0                      100\n");
  char s[51] = {"                                                  "};

  while(1)
  {
    high(9);
    pause(1);
    lightLeft = rc_time(9, 1);
    
    high(5);
    pause(1);
    lightRight = rc_time(5, 1);

    ndiff = 200 * lightRight / (lightRight + lightLeft) - 100;

    print("%c%c", HOME, CRSRDN);
    print("%d        %d          %d", lightLeft, lightRight, ndiff);
    print("%c%c%c", CLREOL, CRSRDN, CR);

    position = (ndiff + 100) / 4;
    s[position] = '*';
    print(s);
    s[position] = ' ';

    pause(350);
  }
}
