#include "ItsyBitsy.h"

Board *board = new ItsyBitsy();

ItsyBitsy::ItsyBitsy(void):
  _pix(new Pix()),
  _ble(new Ble()) {
  ; // empty
}

Board::InitError ItsyBitsy::begin(void) {
  if ((nullptr == _pix) || !(_pix->begin()))
    { return Board::InitError::PIX; }
  if ((nullptr == _ble) || !(_ble->begin()))
    { return Board::InitError::BLE; }

  return InitError::None;
}

void ItsyBitsy::update(void) {
  _pix->update();
  _ble->update();
}
