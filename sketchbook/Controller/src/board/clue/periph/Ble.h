#ifndef __BLE_H__
#define __BLE_H__

// Bluetooth LE
#include <bluefruit.h>

// Project
#include "../../Board.h"
#include "Periph.h"

class Ble {
private:
  uint16_t _connHandle;
  bool _restartScan;

protected:
  AdafruitBluefruit       *_ble;
  BLEClientService        *_neo;
  BLEClientCharacteristic *_stp;
  BLEClientCharacteristic *_fil;

public:
  Ble(void);

  bool begin(void);
  void update(void);

  bool isScanning(void);
  bool scanForDevices(bool scan);
  void onConnect(uint16_t connHandle);
  void onDisconnect(uint16_t connHandle, uint8_t reason);
  void onScanStop(void);
  void onScanResult(ble_gap_evt_adv_report_t *report);

  void subscribeToSensors(void);
  void onAccelerationRelay(Accl accl);
  void onAngularVelocityRelay(Gyro gyro);
  void onMagneticFieldRelay(Mage mage);
  void onTemperatureRelay(Temp temp);
  void onHumidityRelay(Humi humi);
  void onPressureRelay(Psur psur);
  void onAltitudeRelay(Alti alti);
};

#endif // __BLE_H__
