#include "Clue.h"

Board *board = new Clue();

Clue::Clue(void):
    _lcd(new Lcd()),
    _ble(new Ble()),
    _sen(new Sen()) {
  ; // empty
}

Board::InitError Clue::begin(void) {
  if ((nullptr == _lcd) || !(_lcd->begin()))
    { return Board::InitError::LCD; }
  if ((nullptr == _ble) || !(_ble->begin()))
    { return Board::InitError::BLE; }
 if ((nullptr == _sen) || !(_sen->begin()))
   { return Board::InitError::SEN; }

  _lcd->show(View::Kind::Home);

  _ble->scanForDevices(true);
  _ble->subscribeToSensors();

  return InitError::None;
}

void Clue::update(void) {
  _lcd->update();
  _ble->update();
  _sen->update();
}
