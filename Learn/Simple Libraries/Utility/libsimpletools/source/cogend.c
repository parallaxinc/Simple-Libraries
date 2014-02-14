#include "simpletools.h"

void cog_end(int *coginfo)
{
  int cog = *coginfo;
  cogstop(cog);
  free(coginfo); 
}