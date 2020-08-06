#include "ItsyBitsy.h"

Board *board = new ItsyBitsy();

ItsyBitsy::ItsyBitsy(void):
  _ble(new Ble()) {
  ; // empty
}

Board::InitError ItsyBitsy::begin(void) {
  if ((nullptr == _ble) || !(_ble->begin()))
    { return Board::InitError::BLE; }

  return InitError::None;
}

void ItsyBitsy::update(void) {
  _ble->update();
}
