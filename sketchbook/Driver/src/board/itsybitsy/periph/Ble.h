#ifndef __BLE_H__
#define __BLE_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../../NeoCLUE.h"
#include "../../Board.h"

class Ble {
private:
  uint8_t _numConnections;

protected:
  AdafruitBluefruit *_ble;
  BLEDis            *_dis; // device information service
  BLEService        *_neo; // primary NeoCLUE service
  BLECharacteristic *_stp;

public:
  Ble(void);

  bool begin(void);
  void update(void);

  void onConnect(uint16_t connHdl);
  void onDisconnect(uint16_t connHdl, uint8_t reason);
};

extern uint8_t const NEOCLUE_SERVICE_UUID128[16];
extern uint8_t const NEOCLUE_SERVICE_STRIP_CHAR_UUID128[16];

#endif // __BLE_H__
