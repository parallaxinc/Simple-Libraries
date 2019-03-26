


#include "ssd1331.h"

void ssd1331_scrollStart(screen_t* dev, char h, char v) {

  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  // check rotation, move pixel around if necessary
  switch (dev->rotation) {
    case 1:
      gfx_swap(v, h);
      break;
    case 2:
      v = -v;
      h = -h;
      break;
    case 3:
      gfx_swap(v, h);
      h = -h;
      break;
  }

  if(v < 0) v = getDisplayWidth(dev) + v;
  if(h < 0) h = getDisplayHeight(dev) + h;
  if(v > getDisplayWidth(dev)/2) v = getDisplayWidth(dev)/2;
  if(h > getDisplayHeight(dev)/2) h = getDisplayHeight(dev)/2;
  
  ssd1331_writeLockSet(dev->dev_id);

  if (v == 0 && h == 0) {
      ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSTOP, 0);
  } else {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSETUP, 0);
    
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, h, 0);
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 0);
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, getDisplayHeight(dev), 0);    
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, v, 0); 
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 0);   // speed?
  
    int _tMark = CNT + (CLKFREQ / 10000);
    while(_tMark > CNT);                          // Wait for system clock target
  
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSTART, 0);
  }    
  
  ssd1331_writeLockClear(dev->dev_id);
}