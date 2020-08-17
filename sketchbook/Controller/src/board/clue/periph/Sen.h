#ifndef __SEN_H__
#define __SEN_H__

// Big batch of sensors on I2C bus of the CLUE
#include <Adafruit_LSM6DS33.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

// Project
#include "../../Board.h"
#include "Periph.h"

class Sen {
private:
  Accl _accl;
  Gyro _gyro;
  Mage _mage;
  Temp _temp;
  Humi _humi;
  Psur _psur;
  Alti _alti;

protected:
  Adafruit_APDS9960 *_lgp; // light/gesture/proximity
  Adafruit_LSM6DS33 *_agc; // accelerometer/gyroscope
  Adafruit_LIS3MDL  *_mag; // magnetometer
  Adafruit_SHT31    *_thm; // temperature/humidity
  Adafruit_BMP280   *_pal; // pressure/altitude

public:
  Sen(void);

  bool begin(void);
  void update(void);

  Accl acceleration(void)    { return _accl; }
  Gyro angularVelocity(void) { return _gyro; }
  Mage magneticField(void)   { return _mage; }
  Temp temperature(void)     { return _temp; }
  Humi humidity(void)        { return _humi; }
  Psur pressure(void)        { return _psur; }
  Alti altitude(void)        { return _alti; }
};

#endif // __SEN_H__
