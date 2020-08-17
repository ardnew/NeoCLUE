#include "Sen.h"
#include "../Clue.h"

Sen::Sen(void):
    _accl(__SENSORS_REFRESH_ACCEL__),
    _gyro(__SENSORS_REFRESH_GYRO__),
    _mage(__SENSORS_REFRESH_MAGNETO__),
    _temp(__SENSORS_REFRESH_TEMPERATURE__),
    _humi(__SENSORS_REFRESH_HUMIDITY__),
    _psur(__SENSORS_REFRESH_PRESSURE__),
    _alti(__SENSORS_REFRESH_ALTITUDE__),
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
  bool canUpdateTemp = _temp.canUpdate(now);
  bool canUpdateHumi = _humi.canUpdate(now);
  bool canUpdatePsur = _psur.canUpdate(now);
  bool canUpdateAlti = _alti.canUpdate(now);

  // _infof("%d %d %d %d %d %d %d",
  //   canUpdateAccl,
  //   canUpdateGyro,
  //   canUpdateMage,
  //   canUpdateTemp,
  //   canUpdateHumi,
  //   canUpdatePsur,
  //   canUpdateAlti);

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
    model->setAcceleration(acceleration());
  }
  if (canUpdateGyro) {
    _gyro.update(evGyro);
    model->setAngularVelocity(angularVelocity());
  }

  sensors_event_t evMage;
  if (canUpdateMage) {
    _mag->getEvent(&evMage);
    _mage.update(evMage);
    model->setMagneticField(magneticField());
  }

  if (canUpdateTemp) {
    float temp = _thm->readTemperature();
    _temp.update(temp);
    model->setTemperature(temperature());
  }

  if (canUpdateHumi) {
    float humi = 0;// _thm->readHumidity();
    _humi.update(humi);
    model->setHumidity(humidity());
  }

  if (canUpdatePsur) {
    float psur = _pal->readPressure();
    _psur.update(psur);
    model->setPressure(pressure());
  }

  if (canUpdateAlti) {
    float alti = _pal->readAltitude();
    _alti.update(alti);
    model->setAltitude(altitude());
  }
}
