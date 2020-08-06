#ifndef __LCD_H__
#define __LCD_H__

// LCD Graphics
#include <lvgl.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_LvGL_Glue.h>
#include <SPI.h>

// Project
#include "../../../NeoCLUE.h"
#include "../../Board.h"

class Lcd {
public:
  enum class View { None, Home, Scan };

private:
  View _view;
  bool _viewHasAppeared;

  void createView(View view);

protected:
  Adafruit_ST7789    *_ips;
  Adafruit_LvGL_Glue *_glue;

public:
  Lcd(void);

  bool begin(void);
  void update(void);

  void setView(View view);
};

#endif // __LCD_H__
