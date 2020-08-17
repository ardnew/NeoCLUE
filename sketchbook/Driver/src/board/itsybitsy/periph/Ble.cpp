#include "Ble.h"
#include "../ItsyBitsy.h"

const uint8_t NEOCLUE_SERVICE_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_UUID128__;
const uint8_t NEOCLUE_SERVICE_STRIP_CHAR_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__;
const uint8_t NEOCLUE_SERVICE_FILL_CHAR_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_FILL_CHAR_UUID128__;

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

static void bluetoothCharStripWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len) {
  if (nullptr != board) {
    Ble *ble = ((ItsyBitsy *)board)->ble();
    if (nullptr != ble) {
      ble->onCharStripWrite(connHdl, chr, data, len);
    }
  }
}

static void bluetoothCharFillWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len) {
  if (nullptr != board) {
    Ble *ble = ((ItsyBitsy *)board)->ble();
    if (nullptr != ble) {
      ble->onCharFillWrite(connHdl, chr, data, len);
    }
  }
}

Ble::Ble(void):
  _numConnections(0),
  _ble(&Bluefruit),
  _dis(new BLEDis()),
  _neo(new BLEService(NEOCLUE_SERVICE_UUID128)),
  _stp(new Strip(NEOCLUE_SERVICE_STRIP_CHAR_UUID128)),
  _fil(new Fill(NEOCLUE_SERVICE_FILL_CHAR_UUID128)) {
  ; // empty
}

bool Ble::begin(void) {
  if (nullptr == _ble) {
    return false;
  }
  if (!_ble->begin(__BLUETOOTH_CONN_MAX__, 0)) {
    _ble->printInfo();
    return false;
  }
  if (!_ble->setTxPower(__BLUETOOTH_TX_POWER__)) {
    return false;
  }

  _ble->setName(__BLUETOOTH_NAME__);
  _ble->setConnLedInterval(__BLUETOOTH_LED_INTERVAL__);
  _ble->Periph.setConnectCallback(bluetoothConnect);
  _ble->Periph.setDisconnectCallback(bluetoothDisconnect);

  _dis->setManufacturer(__BLUETOOTH_DEVICE_MFG__);
  _dis->setModel(__BLUETOOTH_DEVICE_MODEL__);
  if (ERROR_NONE != _dis->begin()) {
    return false;
  }

  if (ERROR_NONE != _neo->begin()) {
    return false;
  }
  if (!_stp->begin(bluetoothCharStripWrite)) {
    return false;
  }
  _stp->set(__NEOPIXEL_LENGTH_PX__, __NEOPIXEL_ORDER__, __NEOPIXEL_TYPE__);
  _stp->write();

  if (!_fil->begin(bluetoothCharFillWrite)) {
    return false;
  }

  if (!_ble->Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE)) {
    return false;
  }
  if (!_ble->Advertising.addTxPower()) {
    return false;
  }
  if (!_ble->Advertising.addService(*_neo)) {
    return false;
  }
  if (!_ble->ScanResponse.addName()) {
    return false;
  }
  _ble->Advertising.restartOnDisconnect(true);
  _ble->Advertising.setInterval(32, 244); // in unit of 0.625 ms
  _ble->Advertising.setFastTimeout(30);   // number of seconds in fast mode
  if (!_ble->Advertising.start(0)) { // 0 = Don't stop advertising after n seconds
    return false;
  }

  return true;
}

void Ble::update(void) {
  ; // empty
}

void Ble::onConnect(uint16_t connHdl) {
  ++_numConnections;
  if (_numConnections < __BLUETOOTH_CONN_MAX__)
    { _ble->Advertising.start(0); }
}

void Ble::onDisconnect(uint16_t connHdl, uint8_t reason) {
  --_numConnections;
}

void Ble::onCharStripWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len) {
//  _cinfof("received strip data (%d)", len);
//  for (int i = 0; i < len; ++i) {
//    _infof("  stp[%d] = %d", i, data[i]);
//  }
}

void Ble::onCharFillWrite(uint16_t connHdl, BLECharacteristic *chr, uint8_t *data, uint16_t len) {
  _fil->set(data, len);
  if (_fil->isValid()) {
    if (nullptr != board) {
      Pix *pix = ((ItsyBitsy *)board)->pix();
      if (nullptr != pix) {
        pix->fill(_fil->argb(), _fil->start(), _fil->length());
      }
    }
  }
}
