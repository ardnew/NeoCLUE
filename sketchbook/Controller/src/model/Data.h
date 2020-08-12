#ifndef __DATA_H__
#define __DATA_H__

#include "Adafruit_Sensor.h"

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

#endif // __DATA_H__
