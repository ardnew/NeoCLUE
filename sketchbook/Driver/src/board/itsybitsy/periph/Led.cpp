#include "Led.h"
#include "Periph.h"

Led::Led(void):
    _led(new Adafruit_NeoPixel(
        __NEOPIXEL_LENGTH_PX__,
        __NEOPIXEL_DATA_PIN__,
        __NEOPIXEL_ORDER__ | __NEOPIXEL_TYPE__
    )) {
  ; // empty
}

bool Led::begin(void) {
  if (nullptr == _led) {
    return false;
  }

  _led->begin();
  _led->setBrightness(0xFF);
  _led->show();

  return true;
}

void Led::update(void) {
  ; // empty
}
