



#include "ssd1331.h"

void ssd1331_invertDisplay(screen_t *dev, char i) {

  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  ssd1331_writeLockSet(dev->dev_id);

  if (i == 0) {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_NORMALDISPLAY, 0);
  } else {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_INVERTDISPLAY, 0);
  }
  
  ssd1331_writeLockClear(dev->dev_id);
}

