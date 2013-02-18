#include "simpletools.h"

extern _Driver _FileDriver;

FILE* sd_start(void)
{
  add_driver(&_FileDriver);
}