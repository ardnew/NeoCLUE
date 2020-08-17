#include "Pix.h"

Pix::Pix(void):
    _pix(new Adafruit_NeoPixel(
        __NEOPIXEL_LENGTH_PX__,
        __NEOPIXEL_DATA_PIN__,
        __NEOPIXEL_ORDER__ | __NEOPIXEL_TYPE__
    )) {
  ; // empty
}

bool Pix::begin(void) {
  if (nullptr == _pix) {
    return false;
  }

  _pix->begin();
  _pix->setBrightness(0x7F);
  _pix->fill(0x0000FF00);
  _pix->show();

  return true;
}

void Pix::update(void) {
  ; // empty
}
