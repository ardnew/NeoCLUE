#include "Ble.h"
#include "Periph.h"
#include "../ItsyBitsy.h"

uint8_t const NEOCLUE_SERVICE_UUID128[16]            = __NEOCLUE_SERVICE_UUID128__;
uint8_t const NEOCLUE_SERVICE_STRIP_CHAR_UUID128[16] = __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__;

static void bluetoothConnect(uint16_t connHdl) {
  if (nullptr != board) {
    Ble *ble = ((ItsyBitsy *)board)->ble();
    if (nullptr != ble) {
      ble->onConnect(connHdl);
    }
  }
}

static void bluetoothDisconnect(uint16_t connHdl, uint8_t reason) {
  if (nullptr != board) {
    Ble *ble = ((ItsyBitsy *)board)->ble();
    if (nullptr != ble) {
      ble->onDisconnect(connHdl, reason);
    }
  }
}

Ble::Ble(void):
  _numConnections(0),
  _ble(&Bluefruit),
  _dis(new BLEDis()),
  _neo(new BLEService(NEOCLUE_SERVICE_UUID128)),
  _stp(new BLECharacteristic(NEOCLUE_SERVICE_STRIP_CHAR_UUID128)) {
  ; // empty
}

bool Ble::begin(void) {
  _cstamp;
  if (nullptr == _ble) {
    return false;
  }
  _cstamp;
  if (!_ble->begin(__BLUETOOTH_CONN_MAX__, 0)) {
    _ble->printInfo();
    return false;
  }
  _cstamp;
  if (!_ble->setTxPower(__BLUETOOTH_TX_POWER__)) {
    return false;
  }

  _ble->setName(__BLUETOOTH_NAME__);
  _ble->setConnLedInterval(__BLUETOOTH_LED_INTERVAL__);
  _ble->Periph.setConnectCallback(bluetoothConnect);
  _ble->Periph.setDisconnectCallback(bluetoothDisconnect);

  _dis->setManufacturer(__BLUETOOTH_DEVICE_MFG__);
  _dis->setModel(__BLUETOOTH_DEVICE_MODEL__);
  _cstamp;
  if (ERROR_NONE != _dis->begin())
    { return false; }

  _cstamp;
  if (ERROR_NONE != _neo->begin())
    { return false; }

  _stp->setProperties(
    CHR_PROPS_READ | CHR_PROPS_WRITE | CHR_PROPS_WRITE_WO_RESP | CHR_PROPS_INDICATE
  );
  _stp->setPermission(SECMODE_OPEN, SECMODE_OPEN);
  // _stp->setFixedLen(RgbCharStripData::size());
  // _stp->setWriteCallback(bluetoothRgbCharStripWrite);
  _cstamp;
  if (ERROR_NONE != _stp->begin())
    { return false; }

  _cstamp;
  if (!_ble->Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE)) {
    return false;
  }
  _cstamp;
  if (!_ble->Advertising.addTxPower()) {
    return false;
  }
  _cstamp;
  if (!_ble->Advertising.addService(*_neo)) {
    return false;
  }
  _cstamp;
  if (!_ble->ScanResponse.addName()) {
    return false;
  }
  _ble->Advertising.restartOnDisconnect(true);
  _ble->Advertising.setInterval(32, 244); // in unit of 0.625 ms
  _ble->Advertising.setFastTimeout(30);   // number of seconds in fast mode
  _cstamp;
  if (!_ble->Advertising.start(0)) { // 0 = Don't stop advertising after n seconds
    return false;
  }

  _cstamp;
  return true;
}

void Ble::update(void) {
  ; // empty
}

void Ble::onConnect(uint16_t connHdl) {
  ++_numConnections;

  //if (stp->indicateEnabled(connHdl)) {
  //  RgbCharStripData stripData(_numPixels, _colorOrder, _pixelType);
  //  stp->indicate(connHdl, stripData.data(), RgbCharStripData::size());
  //}

  if (_numConnections < __BLUETOOTH_CONN_MAX__)
    { _ble->Advertising.start(0); }
}

void Ble::onDisconnect(uint16_t connHdl, uint8_t reason) {
  --_numConnections;
}
