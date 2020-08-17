#ifndef __LCD_H__
#define __LCD_H__

// LCD Graphics
#include <lvgl.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_LvGL_Glue.h>
#include <SPI.h>

// Project
#include "../../Board.h"
#include "Periph.h"

class Lcd {
private:
  View *_view;

protected:
  Adafruit_ST7789    *_ips;
  Adafruit_LvGL_Glue *_glue;

public:
  Lcd(void);

  bool begin(void);
  void update(void);

  void show(View::Kind kind);
  View *view(void) { return _view; }
};

#endif // __LCD_H__
