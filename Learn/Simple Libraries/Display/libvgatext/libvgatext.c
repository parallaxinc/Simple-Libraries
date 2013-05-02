#include "simpletools.h"  
#include "vgatext.h"

int main()                                    
{
  vga_text_start(8);
  int i;
  while(1)
  {
    vga_text_out(HOME);
    vga_text_str("value = ");
    vga_text_dec(i--);
    vga_text_str("     ");
    pause(200);
  }                                    
}
