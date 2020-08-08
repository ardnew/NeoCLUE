#ifndef __LED_H__
#define __LED_H__

// RGB LED Strip
#include <Adafruit_NeoPixel.h>

// Project
#include "../../../NeoCLUE.h"
#include "../../Board.h"

class Led {
private:
protected:
  Adafruit_NeoPixel *_led;

public:
  Led(void);

  bool begin(void);
  void update(void);
};

#endif // __LED_H__
