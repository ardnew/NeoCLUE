#include "Lcd.h"
#include "../Clue.h"

static void colorPickerEvent(lv_obj_t *obj, lv_event_t event) {
  _cinfof("%s", "color picker event");
  if (nullptr != board) {
    Lcd *lcd = ((Clue *)board)->lcd();
    if (nullptr != lcd) {
      View *view = lcd->view();
      if ((nullptr != view) && (View::Kind::Home == view->kind())) {
        ((Home *)view)->onColorPickerEvent(obj, event);
      }
    }
  }
}

Lcd::Lcd(void):
    _view(nullptr),
    _ips(new Adafruit_ST7789(
        __IPS_LCD_SPI__,
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
        _view = new Home(__IPS_LCD_WIDTH__, __IPS_LCD_HEIGHT__);
        _cinfof("color picker = %p", ((Home *)_view)->colorPicker());
        lv_obj_set_event_cb(((Home *)_view)->colorPicker(), colorPickerEvent);
        break;
      }
      case View::Kind::Scan: {
        _view = new Scan(__IPS_LCD_WIDTH__, __IPS_LCD_HEIGHT__);
        break;
      }
      case View::Kind::None:
      default: {
        break;
      }
    }
    if (nullptr != _view) {
      _view->show();
    }
  }
}
