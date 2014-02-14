#include "simpletools.h"

int *cog_run(void (*function)(void *par), int stacksize)
{
  int *addr;
  addr = malloc(stacksize += 4 + 176 + (stacksize * 4));
  *addr = cogstart(function, NULL, addr + 4, stacksize - 4);
  if(*addr == -1) return (int*) -1;
  return addr;  
}