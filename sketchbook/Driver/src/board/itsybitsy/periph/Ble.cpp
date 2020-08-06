#include "Ble.h"
#include "Periph.h"

Ble::Ble(void):
  _ble(&Bluefruit) {
  ; // empty
}

bool Ble::begin(void) {
  if (nullptr == _ble) {
    return false;
  }
  return true;
}

void Ble::update(void) {
  ; // empty
}
