#ifndef __STRIP_H__
#define __STRIP_H__

// Project
#include "../Cha.h"

class Strip: public Cha {
private:
protected:
  uint16_t  _numPixels;
  uint16_t  _colorOrder;
  uint16_t  _pixelType;
  uint8_t  *_data;
  bool      _isValid;

public:
  Strip(const uint8_t *uuid):
      Cha(uuid),
      _numPixels(0),
      _colorOrder(0),
      _pixelType(0),
      _data(nullptr),
      _isValid(false)
    { /* empty */ }

  bool begin(write_cb_t onWrite);
  void update(void);

  void set(const uint8_t *data, const uint16_t len);
  void set(const uint16_t numPixels, const uint16_t colorOrder, const uint16_t pixelType);
  void write(void);

  bool isValid(void) { return _isValid; }
  uint8_t *data(void) { return _data; }
  uint16_t size(void) { return sizeof(_numPixels) + sizeof(_colorOrder) + sizeof(_pixelType); }

  inline uint16_t numPixels(void) { return _numPixels; }
  inline uint16_t colorOrder(void) { return _colorOrder; }
  inline uint16_t pixelType(void) { return _pixelType; }
};

#endif // __STRIP_H__
