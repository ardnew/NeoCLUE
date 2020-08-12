#include "Sen.h"
#include "../Clue.h"

Sen::Sen(void):
    _accl(__SENSORS_REFRESH_ACCEL__),
    _gyro(__SENSORS_REFRESH_GYRO__),
    _mage(__SENSORS_REFRESH_MAGNETO__),
    _lgp(new Adafruit_APDS9960()),
    _agc(new Adafruit_LSM6DS33()),
    _mag(new Adafruit_LIS3MDL()),
    _thm(new Adafruit_SHT31()),
    _pal(new Adafruit_BMP280()) {
  ; // empty
}

bool Sen::begin(void) {
  if ((nullptr == _lgp) || !(_lgp->begin())) {
    _cerrf("failed to initialize sensor: %s", "light/gesture/proximity (APDS9960)");
    return false;
  }
  if ((nullptr == _agc) || !(_agc->begin_I2C())) {
    _cerrf("failed to initialize sensor: %s", "accelerometer/gyroscope (LSM6DS33)");
    return false;
  }
  if ((nullptr == _mag) || !(_mag->begin_I2C())) {
    _cerrf("failed to initialize sensor: %s", "magnetometer (LIS3MDL)");
    return false;
  }
  if ((nullptr == _thm) || !(_thm->begin())) {
    _cerrf("failed to initialize sensor: %s", "temperature/humidity (SHT30)");
    return false;
  }
  if ((nullptr == _pal) || !(_pal->begin())) {
    _cerrf("failed to initialize sensor: %s", "pressure/altitude (BMP280)");
    return false;
  }

  _lgp->enableProximity(true);
  _lgp->enableGesture(true);

  return true;
}

void Sen::update(void) {
  timespan_t now = millis();

  bool canUpdateAccl = _accl.canUpdate(now);
  bool canUpdateGyro = _gyro.canUpdate(now);
  bool canUpdateMage = _mage.canUpdate(now);

  sensors_event_t evAccl, evGyro;
  if (canUpdateAccl && canUpdateGyro) {
    _agc->getEvent(&evAccl, &evGyro, nullptr);
  } else if (canUpdateAccl) {
    _agc->getEvent(&evAccl, nullptr, nullptr);
  } else if (canUpdateGyro) {
    _agc->getEvent(nullptr, &evGyro, nullptr);
  }
  if (canUpdateAccl) {
    _accl.update(evAccl);
    _infof("accl: (x=%g, y=%g, z=%g)", _accl.x, _accl.y, _accl.z);
  }
  if (canUpdateGyro) {
    _gyro.update(evGyro);
    _infof("    gyro: (x=%g, y=%g, z=%g)", _gyro.x, _gyro.y, _gyro.z);
  }

  sensors_event_t evMage;
  if (canUpdateMage) {
    _mag->getEvent(&evMage);
    _mage.update(evMage);
    _infof("        mage: (x=%g, y=%g, z=%g)", _mage.x, _mage.y, _mage.z);
  }
}

Accl Sen::acceleration(void) {
  return _accl;
}

Gyro Sen::angularVelocity(void) {
  return _gyro;
}

Mage Sen::magneticField(void) {
  return _mage;
}