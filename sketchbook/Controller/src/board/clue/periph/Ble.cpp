#include "Ble.h"
#include "Periph.h"
#include "../Clue.h"

uint8_t const NEOCLUE_SERVICE_UUID128[16]            = __NEOCLUE_SERVICE_UUID128__;
uint8_t const NEOCLUE_SERVICE_STRIP_CHAR_UUID128[16] = __NEOCLUE_SERVICE_STRIP_CHAR_UUID128__;

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
  _isScanning(false),
  _isScanningRestart(false),
  _ble(&Bluefruit) {
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
  return true;
}

void Ble::update(void) {
  ; // empty
}

bool Ble::isScanning(void) {
  return _isScanning;
}

bool Ble::scanForDevices(bool scan) {
  if (_isScanningRestart) {
    // scan restart in progress.
    // don't interrupt.
    // the scan will be started automatically when onScanStop get's fired.
    return false;
  }
  if (scan) {
    // start scan requested.
    if (_isScanning) {
      // scan already in progress.
      // flag for restart and cancel the current scan.
      // subsequent requests to start scan will now return false until the scan
      // has stopped and/or restarted.
      _isScanningRestart = true;
      if (!(_ble->Scanner.stop())) {
        return false;
      }
    } else {
      // no scan in progress.
      // register callbacks and start a new scan.
      _ble->Scanner.setRxCallback(bluetoothScanResult);
      _ble->Scanner.setStopCallback(bluetoothScanStop);
      _ble->Scanner.restartOnDisconnect(true);
      _ble->Scanner.filterRssi(__BLUETOOTH_RSSI_MIN__);
      _ble->Scanner.filterUuid(NEOCLUE_SERVICE_UUID128);      // so only NeoCLUE devices are presented for connection
      _ble->Scanner.setInterval(160, 80); // in units of 0.625 ms
      _ble->Scanner.useActiveScan(true);  // Request scan response data
      if (!(_ble->Scanner.start(0))) {
        return false; // failed to start.
      }
      _isScanning = true;
    }
  } else {
    // stop scan requested.
    if (_isScanning) {
      // scan in progress. send a stop request.
      if (!(_ble->Scanner.stop())) {
        return false;
      }
    }
  }
  return true;
}

void Ble::onScanStop(void) {
  _isScanning = false;
  if (_isScanningRestart) {
    _isScanningRestart = false;
    scanForDevices(true);
  }
}

uint8_t Ble::parseScanResultShortName(uint8_t *buf, size_t len, ble_gap_evt_adv_report_t *report) {
  if (nullptr != buf && nullptr != report && nullptr != _ble) {
    memset(buf, 0, len);
    return _ble->Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME, buf, len);
  }
  return 0;
}

uint8_t Ble::parseScanResultLongName(uint8_t *buf, size_t len, ble_gap_evt_adv_report_t *report) {
  if (nullptr != buf && nullptr != report && nullptr != _ble) {
    memset(buf, 0, len);
    return _ble->Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buf, len);
  }
  return 0;
}

void Ble::onScanResult(ble_gap_evt_adv_report_t *report) {

  static const uint8_t NEOCLUE_SERVICE_UUID128[16] = __NEOCLUE_SERVICE_UUID128__;

  if (report->type.connectable) {
    _infof("-- scan result (%s) ----------------------",
      report->type.scan_response ? "reponse" : "advertisement"
    );
    char addr[18];
    snprintf(addr, 18, "%02X-%02X-%02X-%02X-%02X-%02X",
      report->peer_addr.addr[5],
      report->peer_addr.addr[4],
      report->peer_addr.addr[3],
      report->peer_addr.addr[2],
      report->peer_addr.addr[1],
      report->peer_addr.addr[0]
    );
    _infof("addr: %s", addr);
    _infof("rssi: %d dBm", report->rssi);
    uint8_t name[32];
    if (parseScanResultShortName(name, 32, report)) {
      _infof("short name: %s", name);
    }
    if (parseScanResultLongName(name, 32, report)) {
      _infof("long name: %s", name);
    }
    if (_ble->Scanner.checkReportForUuid(report, NEOCLUE_SERVICE_UUID128)) {
      _infof("%s", "found req'd UUID");
      if (!_ble->Central.connected()) {
        _ble->Central.connect(report);
      }
    }
  }
  _ble->Scanner.resume();
}
