#include "Lcd.h"
#include "Periph.h"

#include "../../../view/home/Home.h"
#include "../../../view/scan/Scan.h"

Lcd::Lcd(void):
  _view(nullptr),
  _ips(new Adafruit_ST7789(
    &__IPS_LCD_SPI__,
    __PIN_IPS_LCD_CS__,
    __PIN_IPS_LCD_DC__,
    __PIN_IPS_LCD_RST__
  )),
  _glue(new Adafruit_LvGL_Glue()) {
  ; // empty
}

bool Lcd::begin(void) {
  if (nullptr == _ips || nullptr == _glue) {
    return false;
  }
  _ips->init(__IPS_LCD_WIDTH__, __IPS_LCD_HEIGHT__);
  _ips->setRotation(__IPS_LCD_ROTATE__);
  _enable_backlight(true);
  return LVGL_OK == _glue->begin(_ips, true);
}

void Lcd::update(void) {
  lv_task_handler();
  if (nullptr != _view) {
    _view->update();
  }
}

void Lcd::show(View::Kind kind) {
  if (nullptr == _view || _view->kind() != kind) {
    if (nullptr != _view) {
      delete _view;
    }
    switch (kind) {
      case View::Kind::Home: {
        _view = new Home();
        break;
      }
      case View::Kind::Scan: {
        _view = new Scan();
        break;
      }
      case View::Kind::None:
      default: {
        break;
      }
    }
  }
}
