#ifndef __FILL_H__
#define __FILL_H__

// Project
#include "../Cha.h"

class Fill: public Cha {
private:
protected:
  uint16_t  _start;
  uint16_t  _length;
  uint32_t  _argb;
  uint8_t  *_data;
  bool      _isValid;

public:
  Fill(const uint8_t *uuid):
      Cha(uuid),
      _start(0),
      _length(0),
      _argb(0),
      _data(nullptr),
      _isValid(true)
    { /* empty */ }

  bool begin(write_cb_t onWrite);
  void update(void);

  void set(const uint8_t *data, const uint16_t len);
  void set(const uint16_t start, const uint16_t length, const uint32_t argb);

  bool isValid(void) { return _isValid; }
  uint8_t *data(void) { return _data; }
  uint16_t size(void) { return sizeof(_start) + sizeof(_length) + sizeof(_argb); }

  inline uint16_t start() { return _start; }
  inline uint16_t length() { return _length; }
  inline uint32_t argb() { return _argb; }
};

#endif // __FILL_H__
