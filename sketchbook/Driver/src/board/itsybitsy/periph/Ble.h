#ifndef __BLE_H__
#define __BLE_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../../NeoCLUE.h"
#include "../../Board.h"

class Ble {
private:
protected:
  AdafruitBluefruit *_ble;

public:
  Ble(void);

  bool begin(void);
  void update(void);
};

#endif // __BLE_H__
