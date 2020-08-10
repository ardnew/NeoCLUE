#ifndef __SEN_H__
#define __SEN_H__

// Big batch of sensors on I2C bus of the CLUE
#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BMP280.h>

// Project
#include "../../Board.h"
#include "Periph.h"

class Sen {
private:
protected:
  Adafruit_LSM6DS33 *_acc;
  Adafruit_LIS3MDL  *_mag;
  Adafruit_SHT31    *_tmu;
  Adafruit_APDS9960 *_plg;
  Adafruit_BMP280   *_psu;

public:
  Sen(void);

  bool begin(void);
  void update(void);
};

#endif // __SEN_H__
