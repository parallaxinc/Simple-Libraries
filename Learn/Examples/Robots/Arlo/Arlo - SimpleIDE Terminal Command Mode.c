/*
  Arlo - SimpleIDE Terminal Command Mode.c
  Communicate with Arlo through the SimpleIDE Terminal.
*/

#include "simpletools.h"
#include "arlodrive.h"

int main()
{
  while(1)
  dhb10_terminal(SIDE_TERM);
  print("Back in main program.");
}
