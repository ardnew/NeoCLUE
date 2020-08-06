#include "Clue.h"

Board *board = new Clue();

Clue::Clue(void):
  _lcd(new Lcd()),
  _ble(new Ble()) {
  ; // empty
}

Board::InitError Clue::begin(void) {
  if ((nullptr == _lcd) || !(_lcd->begin()))
    { return Board::InitError::LCD; }
  if ((nullptr == _ble) || !(_ble->begin()))
    { return Board::InitError::BLE; }

  if (_ble->scanForDevices(true)) {
    _cinfof("%s", "starting scan");
  }

  return InitError::None;
}

void Clue::update(void) {
  _lcd->update();
  _ble->update();
}
