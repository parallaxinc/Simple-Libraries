#include "bme680.h"


/* BME680 API functions */

bme680_device *bme680_init_i2c(i2c *i2c_bus, char i2c_addr) {

  bme680_device* dev = (bme680_device*) malloc(sizeof(bme680_device));
  memset(dev, 0, sizeof(bme680_device));

  dev->i2c_ptr = i2c_bus;
  dev->dev_id = i2c_addr;
  dev->intf = 1;    // i2c interface

  bme680_begin(dev);
  
  return dev;
}


bme680_device *bme680_init_spi(char pin_sdo, char pin_clk, char pin_sdi, char pin_cs) {

  bme680_device* dev = (bme680_device*) malloc(sizeof(bme680_device));
  memset(dev, 0, sizeof(bme680_device));

  dev->sdi_pin = pin_sdi;
  dev->sdo_pin = pin_sdo;
  dev->clk_pin = pin_clk;
  dev->dev_id = pin_cs;
  dev->intf = 0;    // spi interface

  bme680_begin(dev);
  
  return dev;
}


void bme680_begin(bme680_device *dev) {

  unsigned char tmp[] = {0xb6};
  unsigned char cal[44];
  
  bme680_write(dev, (dev->intf ? 0xe0 : 0x60), tmp, 1);
  
  pause(10);
  
  bme680_read(dev, 0x89, cal, 25);
  bme680_read(dev, 0xe1, &cal[25], 16);
  
  tmp[0] = 0x10;
  
  if (!dev->intf) {
    bme680_write(dev, 0x73, tmp, 1);
  }    
  
  bme680_read(dev, 0x02, &cal[41], 1);
  bme680_read(dev, 0x00, &cal[42], 1);
  bme680_read(dev, 0x04, &cal[43], 1);
  
  /* Temperature related coefficients */
  dev->par_t1 = ((unsigned short)((unsigned short) cal[34] << 8) | (unsigned short) cal[33]);
  dev->par_t2 = ((short)((unsigned short) cal[2] << 8) | (unsigned short) cal[1]);
  dev->par_t3 = ((char) cal[3]);
  
  /* Pressure related coefficients */
  dev->par_p1 = ((unsigned short)((unsigned short) cal[6] << 8) | (unsigned short) cal[5]);
  dev->par_p2 = ((short)((unsigned short) cal[8] << 8) | (unsigned short) cal[7]);
  dev->par_p3 = ((char) cal[9]);
  dev->par_p4 = ((short)((unsigned short) cal[12] << 8) | (unsigned short) cal[11]);
  dev->par_p5 = ((short)((unsigned short) cal[14] << 8) | (unsigned short) cal[13]);
  dev->par_p6 = ((char) cal[16]);
  dev->par_p7 = ((char) cal[15]);
  dev->par_p8 = ((short)((unsigned short) cal[20] << 8) | (unsigned short) cal[19]);
  dev->par_p9 = ((short)((unsigned short) cal[22] << 8) | (unsigned short) cal[21]);
  dev->par_p10 = ((unsigned char) cal[23]);
  
  /* Humidity related coefficients */
  dev->par_h1 = ((unsigned short)((unsigned short) cal[27] << 4) | (cal[26] & 0x0F));
  dev->par_h2 = ((unsigned short)((unsigned short) cal[25] << 4) | ((cal[26]) >> 4));
  dev->par_h3 = ((char) cal[28]);
  dev->par_h4 = ((char) cal[29]);
  dev->par_h5 = ((char) cal[30]);
  dev->par_h6 = ((unsigned char) cal[31]);
  dev->par_h7 = ((char) cal[32]);
  
  /* Gas heater related coefficients */
  dev->par_gh1 = ((char) cal[37]);
  dev->par_gh2 = ((short)((unsigned short) cal[36] << 8) | (unsigned short) cal[35]);
  dev->par_gh3 = ((char) cal[38]);
  
  /* Other coefficients */
  dev->res_heat_range = ((cal[41] & 0x30) >> 4);
  dev->res_heat_val = ((char) cal[42]);
  dev->range_sw_err = (((char) cal[43] & (char) 0xF0) >> 4);
  
  /* Configurable Settings */
  dev->amb_temp = 25;                       // Ambient temperature in (C)
  dev->heater_temp = 320;                   // Heater temperature (C)
  dev->heater_duration = 150;               // Heater duration (ms)
  dev->filter_size = BME680_FILTER_SIZE_3;
  dev->temp_oversample = BME680_OS_8X;
  dev->pres_oversample = BME680_OS_4X;
  dev->hum_oversample = BME680_OS_2X;
  dev->sensor_reading_period = 183;

  pause(dev->sensor_reading_period);      // Required time needed for sensor (183 ms for default settings) to take reading (datasheet/example API provides formula...)
}




char bme680_readSensor(bme680_device *dev) {
  char rslt = 0;
  unsigned char buff[15];
  unsigned char tries = 10;
  
  buff[0] = 0x8d;
  bme680_write(dev, 0x74, buff, 1);  // wake up the sensor to take a reading
  
  pause(dev->sensor_reading_period);
    
  while (tries) {
    bme680_read(dev, 0x1d, buff, 15);   //0x9d?

    dev->status = (buff[0] & 0x80) | (buff[14] & 0x20) | (buff[14] & 0x10);

    if (dev->status & 0x80) {
      dev->gas_index = buff[0] & 0x0F;
      dev->meas_index = buff[1];
      
      float var1 = 0;
      float var2 = 0;
      float var3 = 0;
      float var4 = 0;
      const float lookup_k1_range[16] = {0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.8, 0.0, 0.0, -0.2, -0.5, 0.0, -1.0, 0.0, 0.0};
      const float lookup_k2_range[16] = {0.0, 0.0, 0.0, 0.0, 0.1, 0.7, 0.0, -0.8, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      unsigned int adc_meas = 0;
      
      // Temperature conversion
      adc_meas = (unsigned int)(((unsigned int) buff[5] << 12) | ((unsigned int) buff[6] << 4) | ((unsigned int) buff[7] >> 4));
      
      var1 = ((((float) adc_meas / 16384.0) - ((float) dev->par_t1 / 1024.0)) * ((float) dev->par_t2));
      var2 = (((((float) adc_meas / 131072.0) - ((float) dev->par_t1 / 8192.0)) *
          (((float) adc_meas / 131072.0) - ((float) dev->par_t1 / 8192.0))) *
        ((float) dev->par_t3 * 16.0));
      dev->t_fine = (var1 + var2);

      dev->temperature = ((dev->t_fine) / 5120.0);
      
      // Pressure conversion
      adc_meas = (unsigned int)(((unsigned int) buff[2] << 12) | ((unsigned int) buff[3] << 4) | ((unsigned int) buff[4] >> 4));

      var1 = (((float) dev->t_fine / 2.0) - 64000.0);
      var2 = var1 * var1 * (((float) dev->par_p6) / (131072.0));
      var2 = var2 + (var1 * ((float) dev->par_p5) * 2.0);
      var2 = (var2 / 4.0) + (((float) dev->par_p4) * 65536.0);
      var1 = (((((float) dev->par_p3 * var1 * var1) / 16384.0) + ((float) dev->par_p2 * var1)) / 524288.0);
      var1 = ((1.0 + (var1 / 32768.0)) * ((float) dev->par_p1));
      var4 = (1048576.0 - ((float) adc_meas));
    
      if ((int) var1 != 0) {          // Avoid exception caused by division by zero
        var4 = (((var4 - (var2 / 4096.0)) * 6250.0) / var1);
        var1 = (((float) dev->par_p9) * var4 * var4) / 2147483648.0;
        var2 = var4 * (((float) dev->par_p8) / 32768.0);
        var3 = ((var4 / 256.0) * (var4 / 256.0) * (var4 / 256.0) *
          (dev->par_p10 / 131072.0));
        var4 = (var4 + (var1 + var2 + var3 + ((float) dev->par_p7 * 128.0)) / 16.0);
      } else {
        var4 = 0;
      }

      dev->pressure = var4;
      
      // Humidity conversion
      adc_meas = (unsigned int)(((unsigned int) buff[8] << 8) | (unsigned int) buff[9]);

      var4 = ((dev->t_fine) / 5120.0);
    
      var1 = (float)((float) adc_meas) - (((float) dev->par_h1 * 16.0) + (((float) dev->par_h3 / 2.0) *
        var4));
      var2 = var1 * ((float)(((float) dev->par_h2 / 262144.0) * (1.0 + (((float) dev->par_h4 / 16384.0) *
        var4) + (((float) dev->par_h5 / 1048576.0) * var4 * var4))));
      var3 = (float) dev->par_h6 / 16384.0;
    
      var1 = var2 + ((var3 + (((float) dev->par_h7 / 2097152.0) * var4)) * var2 * var2);
    
      if (var1 > 100.0) var1 = 100.0;
      if (var1 < 0.0) var1 = 0.0;

      dev->humidity = var1;
      
      // Gas Resistance conversion
      adc_meas = (unsigned int)((unsigned int) buff[13] << 2 | (((unsigned int) buff[14]) >> 6));
      var1 = (1340.0 + (5.0 * dev->range_sw_err));
      var2 = (var1) * (1.0 + lookup_k1_range[(buff[14] & 0x0F)] / 100.0);
      var3 = 1.0 + (lookup_k2_range[(buff[14] & 0x0F)] / 100.0);
      var1 = 1.0 / (float)(var3 * (0.000000125) * (float)(1 << (buff[14] & 0x0F)) * (((((float) adc_meas) -512.0) / var2) + 1.0));

      dev->gas_resistance = var1;
      
      break;
    }    
    pause(10);
    tries--;
  }

  if (!tries) {
    rslt = -1;
    dev->temperature = 0.0;
    dev->pressure = 0.0;
    dev->altitude = 0.0;
    dev->humidity = 0.0;
    dev->gas_resistance = 0.0;
  }    

  return rslt;
}






char bme680_loadSettings(bme680_device *dev) {
  unsigned char reg_data[7];

  if (dev->heater_temp > 400) dev->heater_temp = 400;

  float var1 = ((((float) dev->par_gh2 / (32768.0)) * (0.0005)) + 0.00235);
  float var2 = ((((float) dev->par_gh1 / (16.0)) + 49.0) * 
    (1.0 + (var1 * (float) dev->heater_temp)));  // Heater temp value
  float var3 = (var2 + (((float) dev->par_gh3 / (1024.0)) * 
    (float) dev->amb_temp));         // Ambient temp value

  reg_data[0] = (unsigned char)(3.4 * ((var3 * (4 / (4 + (float) dev->res_heat_range)) * 
    (1 / (1 + ((float) dev->res_heat_val * 0.002)))) - 25));
  reg_data[1] = 0x64;

  if (dev->heater_duration >= 4032) {     // Heater duration value
    reg_data[4] = 255;
  } else {
    while (dev->heater_duration > 63) {
      dev->heater_duration /= 4;
      reg_data[4] += 64;
    }
    reg_data[4] += dev->heater_duration;
  }

  reg_data[2] = reg_data[4];
  
  bme680_write(dev, 0x5a, reg_data, 3);

  do {
    bme680_read(dev, 0x74, reg_data, 1);
    if (reg_data[0] != 0x8c) {
      reg_data[0] = 0x8c; // Set to sleep
      bme680_write(dev, 0x74, reg_data, 1);
      pause(10);
    }
  } while (reg_data[0] != 0x8c);

  reg_data[0] = ((dev->filter_size << 2) & 0x1C); // Set filter size
  reg_data[1] = 0x74;
  reg_data[2] = ((dev->temp_oversample << 5) & 0xE0) | ((dev->pres_oversample << 2) & 0x1C); // Temp | Pressure oversampling
  reg_data[3] = 0x72;
  reg_data[4] = (dev->hum_oversample & 0x07); // Humidity oversampling
  reg_data[5] = 0x71;
  reg_data[6] = 0x10;

  bme680_write(dev, 0x75, reg_data, 7);

  return 0;
}



void bme680_read(bme680_device *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len) {
  if (dev->intf) {
    while (i2c_busy(dev->i2c_ptr, dev->dev_id)); // Start and Wait for bus to be ready
    i2c_in(dev->i2c_ptr, (unsigned char) dev->dev_id, reg_addr, 1, (unsigned char *) reg_data, len);
    i2c_stop(dev->i2c_ptr);
  } else {    
    low(dev->dev_id);
    shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, (reg_addr | 0x80));
    int bytesIn = 0;
    while (len--)
      reg_data[bytesIn++] = shift_in(dev->sdo_pin, dev->clk_pin, MSBPRE, 8);
    high(dev->dev_id);
  }  
}

void bme680_write(bme680_device *dev, unsigned char reg_addr, unsigned char *reg_data, unsigned short len) {
  if (dev->intf) {
    while (i2c_busy(dev->i2c_ptr, dev->dev_id)); // Start and Wait for bus to be ready
    i2c_out(dev->i2c_ptr, (unsigned char) dev->dev_id, reg_addr, 1, (unsigned char *) reg_data, len);
    i2c_stop(dev->i2c_ptr);
  } else {    
    low(dev->dev_id);
    shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, reg_addr);
    int bytesIn = 0;
    while (len--)
      shift_out(dev->sdi_pin, dev->clk_pin, MSBFIRST, 8, reg_data[bytesIn++]);
    high(dev->dev_id);
  }  
}
