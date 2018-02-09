#include "simpletools.h"
#include "serial.h"
#include "fdserial.h"

char s[10];

int val;

int c;

int main()
{
  print("hello\r");
  print("hello again\n");
  print("hello three");
  print("hello four\r");
  for(int n = 0; n < 6; n++)
  {
    val++;
    print("val = %d\r", val);
    pause(500);
  }
  
  set_endChars(simpleterm_pointer(), "\r\n\0\0"); 
  set_endCharSequence(simpleterm_pointer(), "ab\r\0"); 
  
  print("\n\r");
  print("hello\r");
  print("hello again\n");
  print("hello three");
  print("hello four\r");
  for(int n = 0; n < 6; n++)
  {
    val++;
    print("val = %d\r", val);
    pause(500);
  }
}

