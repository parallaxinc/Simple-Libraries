
#include "ssd1331.h"


void ssd1331_copy(screen_t* dev, int x0, int y0, int x1, int y1, int x2, int y2) {
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
