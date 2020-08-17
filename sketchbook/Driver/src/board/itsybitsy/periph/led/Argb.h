#ifndef __ARGB_H__
#define __ARGB_H__

#define COLOR_BLACK       (argb_t){ .u32 = { blue:   0, green:   0, red:   0, alpha: 255 } }
#define COLOR_NAVY        (argb_t){ .u32 = { blue: 123, green:   0, red:   0, alpha: 255 } }
#define COLOR_DARKGREEN   (argb_t){ .u32 = { blue:   0, green: 125, red:   0, alpha: 255 } }
#define COLOR_DARKCYAN    (argb_t){ .u32 = { blue: 123, green: 125, red:   0, alpha: 255 } }
#define COLOR_MAROON      (argb_t){ .u32 = { blue:   0, green:   0, red: 123, alpha: 255 } }
#define COLOR_PURPLE      (argb_t){ .u32 = { blue: 123, green:   0, red: 123, alpha: 255 } }
#define COLOR_OLIVE       (argb_t){ .u32 = { blue:   0, green: 125, red: 123, alpha: 255 } }
#define COLOR_LIGHTGREY   (argb_t){ .u32 = { blue: 198, green: 195, red: 198, alpha: 255 } }
#define COLOR_DARKGREY    (argb_t){ .u32 = { blue: 123, green: 125, red: 123, alpha: 255 } }
#define COLOR_BLUE        (argb_t){ .u32 = { blue: 255, green:   0, red:   0, alpha: 255 } }
#define COLOR_GREEN       (argb_t){ .u32 = { blue:   0, green: 255, red:   0, alpha: 255 } }
#define COLOR_CYAN        (argb_t){ .u32 = { blue: 255, green: 255, red:   0, alpha: 255 } }
#define COLOR_RED         (argb_t){ .u32 = { blue:   0, green:   0, red: 255, alpha: 255 } }
#define COLOR_MAGENTA     (argb_t){ .u32 = { blue: 255, green:   0, red: 255, alpha: 255 } }
#define COLOR_YELLOW      (argb_t){ .u32 = { blue:   0, green: 255, red: 255, alpha: 255 } }
#define COLOR_WHITE       (argb_t){ .u32 = { blue: 255, green: 255, red: 255, alpha: 255 } }
#define COLOR_ORANGE      (argb_t){ .u32 = { blue:   0, green: 165, red: 255, alpha: 255 } }
#define COLOR_GREENYELLOW (argb_t){ .u32 = { blue:  41, green: 255, red: 173, alpha: 255 } }
#define COLOR_PINK        (argb_t){ .u32 = { blue: 198, green: 130, red: 255, alpha: 255 } }

union argb_t {
  struct __attribute__((packed)) {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
  } u32;
  uint32_t color;
};

class Argb {
private:
  inline static uint8_t clip(const int16_t c) {
    return (c < 0) ? 0U : ( (c > 255) ? 255U : c );
  }
  inline static int16_t interp(
      const int16_t x,
      const int16_t x1, const int16_t y1,
      const int16_t x2, const int16_t y2) {
    float scale = (float)(x - x1);
    float numer = (float)(y2 - x2);
    float denom = (float)(y1 - x1);
    if (fabsf(denom) < __FLOAT32_ABSTOL__) {
      denom = __FLOAT32_ABSTOL__;
    }
    return (int16_t)lroundf(scale * numer / denom) + x2;
  }

protected:
  int16_t _alpha;
  int16_t _red;
  int16_t _green;
  int16_t _blue;

public:
  Argb(void): Argb(COLOR_WHITE)
    { /* empty */ }
  Argb(argb_t const &s):
      _alpha(s.u32.alpha), _red(s.u32.red), _green(s.u32.green), _blue(s.u32.blue)
    { /* empty */ }
  Argb(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 0xFF):
      _alpha(alpha), _red(red), _green(green), _blue(blue)
    { /* empty */ }

  void set(const Argb &argb) {
    set(argb.argb());
  }

  void set(const argb_t &s) { // widens storage (int16_t, 0-padded)
    _alpha = s.u32.alpha;
    _red   = s.u32.red;
    _green = s.u32.green;
    _blue  = s.u32.blue;
  }

  void set(const uint32_t color) {
    _alpha = (uint16_t)((color >> 24U) & 0xFF);
    _red   = (uint16_t)((color >> 16U) & 0xFF);
    _green = (uint16_t)((color >>  8U) & 0xFF);
    _blue  = (uint16_t)((color >>  0U) & 0xFF);
  }

  void set(
      const uint8_t red,
      const uint8_t green,
      const uint8_t blue,
      const uint8_t alpha = 0xFF
  ) {
    _alpha = alpha;
    _red   = red;
    _green = green;
    _blue  = blue;
  }

  argb_t argb(void) const { // narrows storage (uint8_t, clipped)
    return (argb_t){
      .u32 = {
        .blue  = Argb::clip(_blue),
        .green = Argb::clip(_green),
        .red   = Argb::clip(_red),
        .alpha = Argb::clip(_alpha),
      },
    };
  }

  inline bool operator==(const Argb &argb) const {
    return ( _alpha == argb._alpha ) && ( _red  == argb._red  ) &&
           ( _green == argb._green ) && ( _blue == argb._blue ) ;
  }
  inline bool operator!=(const Argb &argb) const {
    return ( _alpha != argb._alpha ) || ( _red  != argb._red  ) ||
           ( _green != argb._green ) || ( _blue != argb._blue ) ;
  }
};

#endif // __ARGB_H__
