#include "Ble.h"
#include "../Clue.h"

const uint8_t NEOCLUE_SERVICE_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_UUID128__;
const uint8_t NEOCLUE_SERVICE_STRIP_CHAR_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__;
const uint8_t NEOCLUE_SERVICE_FILL_CHAR_UUID128[__UUID128_SIZE__] =
    __NEOCLUE_SERVICE_FILL_CHAR_UUID128__;

static void bluetoothConnect(uint16_t connHdl) {
  if (nullptr != board) {
    Ble *ble = ((Clue *)board)->ble();
    if (nullptr != ble) {
      ble->onConnect(connHdl);
    }
  }
}

static void bluetoothDisconnect(uint16_t connHdl, uint8_t reason) {
  if (nullptr != board) {
    Ble *ble = ((Clue *)board)->ble();
    if (nullptr != ble) {
      ble->onDisconnect(connHdl, reason);
    }
  }
}

static void bluetoothScanStop(void) {
  if (nullptr != board) {
    Ble *ble = ((Clue *)board)->ble();
    if (nullptr != ble) {
      ble->onScanStop();
    }
  }
}

static void bluetoothScanResult(ble_gap_evt_adv_report_t *report) {
  if (nullptr != board) {
    Ble *ble = ((Clue *)board)->ble();
    if (nullptr != ble) {
      ble->onScanResult(report);
    }
  }
}

Ble::Ble(void):
    _connHandle(__BLUETOOTH_NO_CONN_HANDLE__),
    _restartScan(false),
    _ble(&Bluefruit),
    _neo(new BLEClientService(NEOCLUE_SERVICE_UUID128)),
    _stp(new BLEClientCharacteristic(NEOCLUE_SERVICE_STRIP_CHAR_UUID128)),
    _fil(new BLEClientCharacteristic(NEOCLUE_SERVICE_FILL_CHAR_UUID128)) {
  ; // empty
}

bool Ble::begin(void) {
  if (nullptr == _ble) {
    return false;
  }
  if (!_ble->begin(0, __BLUETOOTH_CONN_MAX__)) {
    return false;
  }
  if (!_ble->setTxPower(__BLUETOOTH_TX_POWER__)) {
    return false;
  }
  _ble->setName(__BLUETOOTH_NAME__);
  _ble->setConnLedInterval(__BLUETOOTH_LED_INTERVAL__);

  if (!_neo->begin()) {
    return false;
  }
  _stp->begin();
  _fil->begin();

  return true;
}

void Ble::update(void) {
  ; // empty
}

bool Ble::isScanning(void) {
  return nullptr != _ble && _ble->Scanner.isRunning();
}

bool Ble::scanForDevices(bool scan) {
  if (_restartScan) {
    // scan restart in progress.
    // don't interrupt.
    // the scan will be started automatically when onScanStop get's fired.
    return false;
  }
  if (scan) {
    // start scan requested.
    if (isScanning()) {
      // scan already in progress.
      // flag for restart and cancel the current scan.
      // subsequent requests to start scan will now return false until the scan
      // has stopped and/or restarted.
      _restartScan = true;
      if (!(_ble->Scanner.stop())) {
        return false;
      }
    } else {
      // no scan in progress.
      // register callbacks and start a new scan.
      _ble->Central.setConnectCallback(bluetoothConnect);
      _ble->Central.setDisconnectCallback(bluetoothDisconnect);
      _ble->Scanner.setRxCallback(bluetoothScanResult);
      _ble->Scanner.setStopCallback(bluetoothScanStop);
      _ble->Scanner.restartOnDisconnect(true);
      _ble->Scanner.filterRssi(__BLUETOOTH_RSSI_MIN__);
      // we only want NeoCLUE devices to appear in scan results
      _ble->Scanner.filterUuid(NEOCLUE_SERVICE_UUID128);
      _ble->Scanner.setInterval(160, 80); // in units of 0.625 ms
      _ble->Scanner.useActiveScan(true);  // Request scan response data
      if (!(_ble->Scanner.start(__BLUETOOTH_SCAN_TIMEOUT__))) {
        return false; // failed to start.
      }
    }
  } else {
    // stop scan requested.
    if (isScanning()) {
      // scan in progress. send a stop request.
      if (!(_ble->Scanner.stop())) {
        return false;
      }
    }
  }
  return true;
}

void Ble::onConnect(uint16_t connHandle) {
  _connHandle = connHandle;
  if (_neo->discover(connHandle)) {
    if (_stp->discover() && _fil->discover()) {
      model->setIsConnected(true);
      uint8_t stripData[6];
      if (_stp->read(stripData, sizeof(stripData)) >= sizeof(stripData)) {
        model->setNumPixels(((uint16_t)stripData[0] << 8U) | (uint16_t)stripData[1]);
        model->setColorOrder(((uint16_t)stripData[2] << 8U) | (uint16_t)stripData[3]);
        model->setPixelType(((uint16_t)stripData[4] << 8U) | (uint16_t)stripData[5]);
      }
    }
  }
  if (!(model->isConnected())) {
    _ble->disconnect(connHandle);
  }
}

void Ble::onDisconnect(uint16_t connHandle, uint8_t reason) {
  _connHandle = __BLUETOOTH_NO_CONN_HANDLE__;
  model->setIsConnected(false);
  model->setPeerAddr(nullptr);
}

void Ble::onScanStop(void) {
  if (_restartScan) {
    _restartScan = false;
    scanForDevices(true);
  }
}

void Ble::onScanResult(ble_gap_evt_adv_report_t *report) {
  bool isConnected = false;
  if (report->type.connectable) {
    // verify the UUID again, which should always be true because of the call
    // to filterUuid() in scanForDevices().
    if (_ble->Scanner.checkReportForUuid(report, NEOCLUE_SERVICE_UUID128)) {
      // attempt connection
      isConnected = _ble->Central.connect(report);
      if (isConnected) {
        // update _peerAddr to refer to our active connection.
        model->setPeerAddr(report->peer_addr.addr);
      }
    }
  }
  if (!isConnected) {
    _ble->Scanner.resume();
  }
}

void Ble::subscribeToSensors(void) {
  model->accelerationRelay()->subscribe(this, &Ble::onAccelerationRelay);
  model->angularVelocityRelay()->subscribe(this, &Ble::onAngularVelocityRelay);
  model->magneticFieldRelay()->subscribe(this, &Ble::onMagneticFieldRelay);
  model->temperatureRelay()->subscribe(this, &Ble::onTemperatureRelay);
  model->humidityRelay()->subscribe(this, &Ble::onHumidityRelay);
  model->pressureRelay()->subscribe(this, &Ble::onPressureRelay);
  model->altitudeRelay()->subscribe(this, &Ble::onAltitudeRelay);
}

void Ble::onAccelerationRelay(Accl accl) {
  uint16_t start = 0;
  uint16_t numPixels = model->numPixels();
  uint32_t argb = accl.toArgb();
  if (model->isConnected() && (numPixels > 0)) {
    uint8_t fillData[8];
    fillData[0] = (uint8_t)((start  >> 8U) & 0xFF);
    fillData[1] = (uint8_t)((start  >> 0U) & 0xFF);
    fillData[2] = (uint8_t)((numPixels >> 8U) & 0xFF);
    fillData[3] = (uint8_t)((numPixels >> 0U) & 0xFF);
    fillData[4] = (uint8_t)((argb >> 24U) & 0xFF);
    fillData[5] = (uint8_t)((argb >> 16U) & 0xFF);
    fillData[6] = (uint8_t)((argb >>  8U) & 0xFF);
    fillData[7] = (uint8_t)((argb >>  0U) & 0xFF);
    _fil->write(fillData, sizeof(fillData));
  }
}

void Ble::onAngularVelocityRelay(Gyro gyro) {

}

void Ble::onMagneticFieldRelay(Mage mage) {

}

void Ble::onTemperatureRelay(Temp temp) {

}

void Ble::onHumidityRelay(Humi humi) {

}

void Ble::onPressureRelay(Psur psur) {

}

void Ble::onAltitudeRelay(Alti alti) {

}
