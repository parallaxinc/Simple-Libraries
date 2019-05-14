


#include "ssd1331.h"

void ssd1331_scrollDisplay(screen_t* dev, int h, int v) {

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

  
  if(h > dev->width) h = dev->width;
  if(v > dev->height/2) v = dev->height/2;
  if(h < 0 - dev->width) h = 0 - dev->width;
  if(v < dev->height/(-2)) v = dev->height/(-2);

  if(h < 0) h = dev->width + h;
  if(v < 0) v = dev->height + v;
  
  ssd1331_writeLockSet(dev->dev_id);

  if (v == 0 && h == 0) {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSTOP, 0);
  } else {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSETUP, 0);
    
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, (char) h, 0);
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 0);
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, dev->width << 1, 0);    
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, (char) v, 0); 
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, 0, 0);   // speed?    
  
    int _tMark = CNT + (CLKFREQ / 10000);
    while(_tMark > CNT);                          // Wait for system clock target
  
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_SCROLLSTART, 0);
  }    
  
  ssd1331_writeLockClear(dev->dev_id);
}