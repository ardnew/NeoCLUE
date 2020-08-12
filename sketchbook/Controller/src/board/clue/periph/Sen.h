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

class Xyz {
protected:
  timespan_t _updateRate; // milliseconds
  timespan_t _updateLast; //
public:
  float x, y, z;
  constexpr Xyz(void):
      _updateRate(__TIMESPAN_MAX__),
      _updateLast(0),
      x(0), y(0), z(0)
    { /* empty */ }
  constexpr Xyz(const timespan_t refresh):
      _updateRate(refresh),
      _updateLast(0),
      x(0), y(0), z(0)
    { /* empty */ }
  constexpr Xyz(const timespan_t refresh, const sensors_vec_t &vec):
      _updateRate(refresh),
      _updateLast(0),
      x(vec.x), y(vec.y), z(vec.z)
    { /* empty */ }
  inline bool canUpdate(const timespan_t curr) {
    return
      (0 == _updateLast) || (
          (curr < _updateLast) // timer overflow?
            ? ((__TIMESPAN_MAX__ - _updateLast) + curr)
            : (curr - _updateLast)
        ) > _updateRate;
  }
  inline void update(const timespan_t curr, const sensors_vec_t &vec)
    { x = vec.x; y = vec.y; z = vec.z; _updateLast = curr; }
  inline void update(const sensors_vec_t &vec)
    { update(millis(), vec); }
  inline bool operator==(const Xyz &o) const
    { return (o.x == x) && (o.y == y) && (o.z == z); }
  inline bool operator!=(const Xyz &o) const
    { return (o.x != x) || (o.y != y) || (o.z != z); }
};

class Accl: public Xyz {
public:
  constexpr Accl(void):
      Xyz()
    { /* empty */ }
  constexpr Accl(const timespan_t refresh):
      Xyz(refresh)
    { /* empty */ }
  inline void update(const sensors_event_t &ev)
    { Xyz::update(ev.acceleration); }
};

class Gyro: public Xyz {
public:
  constexpr Gyro(void):
      Xyz()
    { /* empty */ }
  constexpr Gyro(const timespan_t refresh):
      Xyz(refresh)
    { /* empty */ }
  inline void update(const sensors_event_t &ev)
    { Xyz::update(ev.gyro); }
};

class Mage: public Xyz {
public:
  constexpr Mage(void):
      Xyz()
    { /* empty */ }
  constexpr Mage(const timespan_t refresh):
      Xyz(refresh)
    { /* empty */ }
  inline void update(const sensors_event_t &ev)
    { Xyz::update(ev.magnetic); }
};

class Sen {
private:
  Accl _accl;
  Gyro _gyro;
  Mage _mage;

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

  Accl acceleration(void);
  Gyro angularVelocity(void);
  Mage magneticField(void);
};

#endif // __SEN_H__
