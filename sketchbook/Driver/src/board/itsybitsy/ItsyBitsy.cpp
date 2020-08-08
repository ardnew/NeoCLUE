#include "ItsyBitsy.h"

Board *board = new ItsyBitsy();

ItsyBitsy::ItsyBitsy(void):
  _led(new Led()),
  _ble(new Ble()) {
  ; // empty
}

Board::InitError ItsyBitsy::begin(void) {
  if ((nullptr == _led) || !(_led->begin()))
    { return Board::InitError::LED; }
  if ((nullptr == _ble) || !(_ble->begin()))
    { return Board::InitError::BLE; }

  return InitError::None;
}

void ItsyBitsy::update(void) {
  _led->update();
  _ble->update();
}
