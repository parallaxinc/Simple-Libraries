
#include "ssd1331.h"



void ssd1331_sleepWakeDisplay(screen_t* dev, char i) {  
  int mask_cs =  (1 << dev->dev_id);
  int mask_sdi = (1 << dev->sdi_pin);
  int mask_clk = (1 << dev->clk_pin);
  int mask_dc =  (1 << dev->dc_pin);

  ssd1331_writeLockSet(dev->dev_id);

  if(i) {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DISPLAYOFF, 0);    //--turn off oled panel
  } else {
    ssd1331_writeByte(mask_cs, mask_sdi, mask_clk, mask_dc, SSD1331_CMD_DISPLAYON, 0);     //--turn on oled panel
  }        

  ssd1331_writeLockClear(dev->dev_id);
}