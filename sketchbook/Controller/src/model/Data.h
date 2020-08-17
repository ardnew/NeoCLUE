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

#define _c2f(c) (((c) * 9.0F / 5.0F) + 32.0F)
class Temp {
protected:
  timespan_t _updateRate; // milliseconds
  timespan_t _updateLast; //
public:
  float celsius;
  float fahrenheit;
  constexpr Temp(void):
      _updateRate(__TIMESPAN_MAX__),
      _updateLast(0),
      celsius(0),
      fahrenheit(_c2f(0))
    { /* empty */ }
  constexpr Temp(const timespan_t refresh):
      _updateRate(refresh),
      _updateLast(0),
      celsius(0),
      fahrenheit(_c2f(0))
    { /* empty */ }
  constexpr Temp(const timespan_t refresh, const float c):
      _updateRate(refresh),
      _updateLast(0),
      celsius(c),
      fahrenheit(_c2f(c))
    { /* empty */ }
  inline bool canUpdate(const timespan_t curr) {
    return
      (0 == _updateLast) || (
          (curr < _updateLast) // timer overflow?
            ? ((__TIMESPAN_MAX__ - _updateLast) + curr)
            : (curr - _updateLast)
        ) > _updateRate;
  }
  inline void update(const timespan_t curr, const float c)
    { celsius = c; fahrenheit = _c2f(c); _updateLast = curr; }
  inline void update(const float c)
    { update(millis(), c); }
  inline bool operator==(const Temp &o) const
    { return (o.celsius == celsius) && (o.fahrenheit == fahrenheit); }
  inline bool operator!=(const Temp &o) const
    { return (o.celsius != celsius) || (o.fahrenheit != fahrenheit); }
};
#undef _c2f

class Humi {
protected:
  timespan_t _updateRate; // milliseconds
  timespan_t _updateLast; //
public:
  float percent;
  constexpr Humi(void):
      _updateRate(__TIMESPAN_MAX__),
      _updateLast(0),
      percent(0)
    { /* empty */ }
  constexpr Humi(const timespan_t refresh):
      _updateRate(refresh),
      _updateLast(0),
      percent(0)
    { /* empty */ }
  constexpr Humi(const timespan_t refresh, const float pct):
      _updateRate(refresh),
      _updateLast(0),
      percent(pct)
    { /* empty */ }
  inline bool canUpdate(const timespan_t curr) {
    return
      (0 == _updateLast) || (
          (curr < _updateLast) // timer overflow?
            ? ((__TIMESPAN_MAX__ - _updateLast) + curr)
            : (curr - _updateLast)
        ) > _updateRate;
  }
  inline void update(const timespan_t curr, const float pct)
    { percent = pct; _updateLast = curr; }
  inline void update(const float pct)
    { update(millis(), pct); }
  inline bool operator==(const Humi &o) const
    { return (o.percent == percent); }
  inline bool operator!=(const Humi &o) const
    { return (o.percent != percent); }
};

class Psur {
protected:
  timespan_t _updateRate; // milliseconds
  timespan_t _updateLast; //
public:
  float pascal;
  constexpr Psur(void):
      _updateRate(__TIMESPAN_MAX__),
      _updateLast(0),
      pascal(0)
    { /* empty */ }
  constexpr Psur(const timespan_t refresh):
      _updateRate(refresh),
      _updateLast(0),
      pascal(0)
    { /* empty */ }
  constexpr Psur(const timespan_t refresh, const float pas):
      _updateRate(refresh),
      _updateLast(0),
      pascal(pas)
    { /* empty */ }
  inline bool canUpdate(const timespan_t curr) {
    return
      (0 == _updateLast) || (
          (curr < _updateLast) // timer overflow?
            ? ((__TIMESPAN_MAX__ - _updateLast) + curr)
            : (curr - _updateLast)
        ) > _updateRate;
  }
  inline void update(const timespan_t curr, const float pas)
    { pascal = pas; _updateLast = curr; }
  inline void update(const float pas)
    { update(millis(), pas); }
  inline bool operator==(const Psur &o) const
    { return (o.pascal == pascal); }
  inline bool operator!=(const Psur &o) const
    { return (o.pascal != pascal); }
};

class Alti {
protected:
  timespan_t _updateRate; // milliseconds
  timespan_t _updateLast; //
public:
  float meters;
  constexpr Alti(void):
      _updateRate(__TIMESPAN_MAX__),
      _updateLast(0),
      meters(0)
    { /* empty */ }
  constexpr Alti(const timespan_t refresh):
      _updateRate(refresh),
      _updateLast(0),
      meters(0)
    { /* empty */ }
  constexpr Alti(const timespan_t refresh, const float m):
      _updateRate(refresh),
      _updateLast(0),
      meters(m)
    { /* empty */ }
  inline bool canUpdate(const timespan_t curr) {
    return
      (0 == _updateLast) || (
          (curr < _updateLast) // timer overflow?
            ? ((__TIMESPAN_MAX__ - _updateLast) + curr)
            : (curr - _updateLast)
        ) > _updateRate;
  }
  inline void update(const timespan_t curr, const float m)
    { meters = m; _updateLast = curr; }
  inline void update(const float m)
    { update(millis(), m); }
  inline bool operator==(const Alti &o) const
    { return (o.meters == meters); }
  inline bool operator!=(const Alti &o) const
    { return (o.meters != meters); }
};

#endif // __DATA_H__
