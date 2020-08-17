#ifndef __LED_H__
#define __LED_H__

#define __LED_INVALID_POS__   (-1)

class Led {
protected:
  Argb    _argb;
  int16_t _pos;

public:
  Led(void):
      _argb(),
      _pos(__LED_INVALID_POS__)
    { /* empty */ }
  Led(const argb_t &argb, const int16_t pos):
      _argb(argb),
      _pos(pos)
    { /* empty */ }

  Argb color(void) { return _argb; }
  void setColor(const argb_t &argb) { _argb.set(argb); }
  void setColor(const uint32_t color) { _argb.set(color); }
  void setColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 0xFF) {
    _argb.set(red, green, blue, alpha);
  }

  int16_t position(void) { return _pos; }
  void setPosition(const int16_t pos) { _pos = pos; }
  bool isValid(void) { return _pos > __LED_INVALID_POS__; }

  void fill(Adafruit_NeoPixel * const pix) {
    pix->clear();
    pix->fill(pix->gamma32(color().color));
    pix->show();
  }
};

#endif // __LED_H__
