#include "Fill.h"

bool Fill::begin(write_cb_t onWrite) {
  setProperties(
    CHR_PROPS_READ | CHR_PROPS_WRITE | CHR_PROPS_WRITE_WO_RESP
  );
  setPermission(SECMODE_OPEN, SECMODE_OPEN);
  setFixedLen(size());
  setWriteCallback(onWrite);

  return ERROR_NONE == BLECharacteristic::begin();
}

void Fill::update(void) {

}

void Fill::set(const uint8_t *data, const uint16_t len) {
  if (nullptr == _data) {
    _data = (uint8_t *)malloc(size());
  }
  _isValid = (nullptr != _data) && (len >= size());
  if (_isValid) {
    _start         = ((uint16_t)data[0] << 8U) | (uint16_t)data[1];
    _length        = ((uint16_t)data[2] << 8U) | (uint16_t)data[3];
    _argb          = ((uint32_t)data[4] << 24U) | ((uint32_t)data[5] << 16U) | \
                     ((uint32_t)data[6] <<  8U) | (uint32_t)data[7];
    memcpy(_data, data, size());
  }
}

void Fill::set(const uint16_t start, const uint16_t length, const uint32_t argb) {
  if (nullptr == _data) {
    _data = (uint8_t *)malloc(size());
  }
  _isValid = nullptr != _data;
  if (_isValid) {
    _start = start;
    _data[0] = (uint8_t)((_start  >> 8U) & 0xFF);
    _data[1] = (uint8_t)((_start  >> 0U) & 0xFF);
    _length = length;
    _data[2] = (uint8_t)((_length >> 8U) & 0xFF);
    _data[3] = (uint8_t)((_length >> 0U) & 0xFF);
    _argb = argb;
    _data[4] = (uint8_t)((_argb >> 24U) & 0xFF);
    _data[5] = (uint8_t)((_argb >> 16U) & 0xFF);
    _data[6] = (uint8_t)((_argb >>  8U) & 0xFF);
    _data[7] = (uint8_t)((_argb >>  0U) & 0xFF);
  }
}

void Fill::write(void) {
  if (_isValid) {
    BLECharacteristic::write(_data, size());
  }
}
