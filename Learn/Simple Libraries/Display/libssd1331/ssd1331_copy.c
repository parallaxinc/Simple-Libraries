
#include "ssd1331.h"


void ssd1331_copy(screen_t* dev, int x0, int y0, int w, int h, int x2, int y2) {
  int x1 = x0 + w - 1;
  int y1 = y0 + h - 1;
  
  int x3 = x2 + w - 1;
  int y3 = y2 + h - 1;

  if (x0 >= getDisplayWidth(dev) || y0 >= getDisplayHeight(dev) || x1 < 0 || y1 < 0 || w <= 0 || h <= 0 || 
      x2 >= getDisplayWidth(dev) || y2 >= getDisplayHeight(dev) || x3 < 0 || y3 < 0) {
    return;
  }    

  if (x1 >= getDisplayWidth(dev)) {
    x1 = getDisplayWidth(dev) - 1;
    w = x1 - x0 + 1;
  }    
  
  if (y1 >= getDisplayHeight(dev)) {
    y1 = getDisplayHeight(dev) - 1;
    h = y1 - y0 + 1;
  }     
 
  if (x0 < 0) {
    x2 = x2 - x0;
    x0 = 0;
  }    
  
  if (y0 < 0) {
    y2 = y2 - y0;
    y0 = 0;
  }
  
  x3 = x2 + w - 1;
  y3 = y2 + h - 1;
 
  if(x3 >= getDisplayWidth(dev)) {
    x3 = getDisplayWidth(dev) - 1;
    w = x3 - x2 + 1;
    x1 = x0 + w - 1;
  }    
  
  if(y3 >= getDisplayHeight(dev)) {
    y3 = getDisplayHeight(dev) - 1;
    h = y3 - y2 + 1;
    y1 = y0 + h - 1;
  }    


  // check rotation, move pixel around if necessary
  switch (dev->rotation) {
    case 1:
      gfx_swap(x0, y0);
      gfx_swap(x1, y1);
      gfx_swap(x2, y2);
      gfx_swap(x3, y3);
      x0 = dev->width - x0 - 1;
      x1 = dev->width - x1 - 1;
      x2 = dev->width - x2 - 1;
      x3 = dev->width - x3 - 1;
      break;
    case 2:
      x0 = dev->width - x0 - 1;
      y0 = dev->height - y0 - 1;
      x1 = dev->width - x1 - 1;
      y1 = dev->height - y1 - 1;
      x2 = dev->width - x2 - 1;
      y2 = dev->height - y2 - 1;
      x3 = dev->width - x3 - 1;
      y3 = dev->height - y3 - 1;
      gfx_swap(x0, x1);
      gfx_swap(y0, y1);
      gfx_swap(x2, x3);
      gfx_swap(y2, y3);
      break;
    case 3:
      gfx_swap(x0, y0);
      gfx_swap(x1, y1);
      gfx_swap(x2, y2);
      gfx_swap(x3, y3);
      y0 = dev->height - y0 - 1;
      y1 = dev->height - y1 - 1;
      y2 = dev->height - y2 - 1;
      y3 = dev->height - y3 - 1;
      break;
  }

  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  ssd1331_writeLockSet(dev->dev_id);  

  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_COPY, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, x0, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, y0, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, x1, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, y1, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, x2, 0);
  ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, y2, 0);

  int _tMark = CNT + (CLKFREQ / 2000);
  while(_tMark > CNT);                          // Wait for system clock target

  ssd1331_writeLockClear(dev->dev_id);
}
