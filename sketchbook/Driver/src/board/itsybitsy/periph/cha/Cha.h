#ifndef __CHA_H__
#define __CHA_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../../../NeoCLUE.h"

class Cha: public BLECharacteristic {
private:
protected:
public:
  Cha(void)
    { /* empty */ }
  Cha(const uint8_t *uuid):
      BLECharacteristic(uuid)
    { /* empty */ }

  virtual bool begin(write_cb_t onWrite) = 0;
  virtual void update(void) = 0;

  virtual void set(const uint8_t *data, const uint16_t len) = 0;

  virtual bool isValid(void) = 0;
  virtual uint8_t *data(void) = 0;
  virtual uint16_t size(void) = 0;
};

#endif // __CHA_H__
