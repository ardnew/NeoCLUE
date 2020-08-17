#ifndef __BLE_H__
#define __BLE_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../Board.h"
#include "Periph.h"
#include "cha/Cha.h"
#include "cha/strip/Strip.h"
#include "cha/fill/Fill.h"

class Ble {
private:
  uint8_t _numConnections;

protected:
  AdafruitBluefruit *_ble;
  BLEDis            *_dis; // device information service
  BLEService        *_neo; // primary NeoCLUE service
  Strip             *_stp;
  Fill              *_fil;

public:
  Ble(void);

  bool begin(void);
  void update(void);

  void onConnect(uint16_t connHdl);
  void onDisconnect(uint16_t connHdl, uint8_t reason);
  void onCharStripWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len);
  void onCharFillWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len);
};

#endif // __BLE_H__
