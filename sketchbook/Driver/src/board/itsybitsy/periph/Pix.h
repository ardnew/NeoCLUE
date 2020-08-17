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
};

#endif // __PIX_H__
