#ifndef __PIX_H__
#define __PIX_H__

// RGB LED Strip
#include <Adafruit_NeoPixel.h>

// Project
#include "../../Board.h"
#include "Periph.h"

class Pix {
private:
protected:
  Adafruit_NeoPixel *_pix;

public:
  Pix(void);

  bool begin(void);
  void update(void);

  void fill(const uint32_t color = 0, const uint16_t start = 0, const uint16_t length = 0);
};

#endif // __PIX_H__
