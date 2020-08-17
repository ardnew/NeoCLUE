#include "Strip.h"

bool Strip::begin(write_cb_t onWrite) {
  setProperties(
    CHR_PROPS_READ | CHR_PROPS_WRITE | CHR_PROPS_WRITE_WO_RESP | CHR_PROPS_INDICATE
  );
  setPermission(SECMODE_OPEN, SECMODE_OPEN);
  setFixedLen(size());
  setWriteCallback(onWrite);

  return ERROR_NONE == BLECharacteristic::begin();
}

void Strip::update(void) {

}

void Strip::set(const uint8_t *data, const uint16_t len) {
  if (nullptr == _data) {
    _data = (uint8_t *)malloc(size());
  }
  _isValid = (nullptr != _data) && (len >= size());
  if (_isValid) {
    _numPixels  = ((uint16_t)data[0] << 8U) | (uint16_t)data[1];
    _colorOrder = ((uint16_t)data[2] << 8U) | (uint16_t)data[3];
    _pixelType  = ((uint16_t)data[4] << 8U) | (uint16_t)data[5];
    memcpy(_data, data, size());
  }
}

void Strip::set(const uint16_t numPixels, const uint16_t colorOrder, const uint16_t pixelType) {
  if (nullptr == _data) {
    _data = (uint8_t *)malloc(size());
  }
  _isValid = nullptr != _data;
  if (_isValid) {
    _numPixels = numPixels;
    _data[0] = (uint8_t)((_numPixels  >> 8U) & 0xFF);
    _data[1] = (uint8_t)((_numPixels  >> 0U) & 0xFF);
    _colorOrder = colorOrder;
    _data[2] = (uint8_t)((_colorOrder >> 8U) & 0xFF);
    _data[3] = (uint8_t)((_colorOrder >> 0U) & 0xFF);
    _pixelType = pixelType;
    _data[4] = (uint8_t)((_pixelType  >> 8U) & 0xFF);
    _data[5] = (uint8_t)((_pixelType  >> 0U) & 0xFF);
  }
}

void Strip::write(void) {
  if (_isValid) {
    BLECharacteristic::write(_data, size());
  }
}
