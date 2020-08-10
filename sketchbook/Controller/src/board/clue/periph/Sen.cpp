#include "Sen.h"
#include "../Clue.h"

Sen::Sen(void):
  _acc(new Adafruit_LSM6DS33()),
  _mag(new Adafruit_LIS3MDL()),
  _tmu(new Adafruit_SHT31()),
  _plg(new Adafruit_APDS9960()),
  _psu(new Adafruit_BMP280()) {
  ; // empty
}

bool Sen::begin(void) {
  if ((nullptr == _plg) || !(_plg->begin())) {
    _cerrf("failed to initialize: %s", "APDS9960");
    return false;
  }
  if ((nullptr == _acc) || !(_acc->begin_I2C())) {
    _cerrf("failed to initialize: %s", "LSM6DS33");
    return false;
  }
  if ((nullptr == _mag) || !(_mag->begin_I2C())) {
    _cerrf("failed to initialize: %s", "LIS3MDL");
    return false;
  }
  if ((nullptr == _tmu) || !(_tmu->begin())) {
    _cerrf("failed to initialize: %s", "SHT30");
    return false;
  }
  if ((nullptr == _psu) || !(_psu->begin())) {
    _cerrf("failed to initialize: %s", "BMP280");
    return false;
  }

  _plg->enableColor(true);

  return true;
}

void Sen::update(void) {
  ; // empty
}
