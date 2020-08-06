#ifndef __BLE_H__
#define __BLE_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../../NeoCLUE.h"
#include "../../Board.h"

class Ble {
private:
  bool _isScanning;
  bool _isScanningRestart;

protected:
  AdafruitBluefruit *_ble;

public:
  Ble(void);

  bool begin(void);
  void update(void);

  bool isScanning(void);
  bool scanForDevices(bool scan);
  void onScanStop(void);
  void onScanResult(ble_gap_evt_adv_report_t *report);
  uint8_t parseScanResultShortName(uint8_t *buf, size_t len, ble_gap_evt_adv_report_t *report);
  uint8_t parseScanResultLongName(uint8_t *buf, size_t len, ble_gap_evt_adv_report_t *report);
};

#endif // __BLE_H__
