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
  _pix->show();

  return true;
}

void Pix::update(void) {
  ; // empty
}

void Pix::fill(const uint32_t color, const uint16_t start, const uint16_t length) {
  _pix->fill(color, start, length);
  _pix->show();
}
