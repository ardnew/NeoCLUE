#include "Lcd.h"
#include "Periph.h"

Lcd::Lcd(void):
  _view(View::None),
  _viewHasAppeared(false),
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
  setView(View::Home);
  return LVGL_OK == _glue->begin(_ips, true);
}

void Lcd::update(void) {
  lv_task_handler();
  if (!_viewHasAppeared) {
    createView(_view);
    _viewHasAppeared = true;
  }
}

void Lcd::setView(View view) {
  if (_view != view) {
    // requested a view other than the currently displayed view.
    // reset the appearance flag so it gets created on next screen update.
    _view = view;
    _viewHasAppeared = false;
  }
}

void Lcd::createView(View view) {
  switch (view) {
    case View::None: {
      break;
    }
    case View::Home: {
      lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "---OK2---");
      lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
      break;
    }
    case View::Scan: {
      break;
    }
  }
}
