#include "Ble.h"
#include "../Clue.h"

uint8_t const NEOCLUE_SERVICE_UUID128[__UUID128_SIZE__] =
  __NEOCLUE_SERVICE_UUID128__;
uint8_t const NEOCLUE_SERVICE_STRIP_CHAR_UUID128[__UUID128_SIZE__] =
  __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__;

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
  _ble(&Bluefruit) {
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
  model->setIsConnected(true);
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
