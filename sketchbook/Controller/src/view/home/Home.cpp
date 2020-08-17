#include "Home.h"
#include "../../util/Util.h"

#define __BLUETOOTH_PEER_NOT_CONNECTED_STR__  "Scanning...\0"

Home::Home(void):
    _screen(lv_obj_create(nullptr, nullptr)),
    _btsymLabel(nullptr),
    _peerLabel(nullptr),
    _tabView(nullptr),
    _tabColor(nullptr),
    _colorPicker(nullptr),
    _colorRedLabel(nullptr),
    _colorGreenLabel(nullptr),
    _colorBlueLabel(nullptr),
    _colorXLabel(nullptr),
    _colorYLabel(nullptr),
    _colorZLabel(nullptr) {
  memset(_peerAddr, 0, __BLUETOOTH_PEER_ADDR_STRLEN__);
}

Home::Home(const uint16_t width, const uint16_t height):
    Home() {

  lv_obj_set_pos(_screen, 0, 0);
  lv_obj_set_size(_screen, width, height);

  initStatusBar(_screen, width, height);
  initTabView(_screen, width, height);

  model->clearRelays();
  model->isConnectedRelay()->subscribe(this, &Home::onIsConnectedRelay);
  model->peerAddrRelay()->subscribe(this, &Home::onPeerAddrRelay);
  model->accelerationRelay()->subscribe(this, &Home::onAccelerationRelay);
  model->angularVelocityRelay()->subscribe(this, &Home::onAngularVelocityRelay);
  model->magneticFieldRelay()->subscribe(this, &Home::onMagneticFieldRelay);
  model->temperatureRelay()->subscribe(this, &Home::onTemperatureRelay);
  model->humidityRelay()->subscribe(this, &Home::onHumidityRelay);
  model->pressureRelay()->subscribe(this, &Home::onPressureRelay);
  model->altitudeRelay()->subscribe(this, &Home::onAltitudeRelay);
}

Home::~Home(void) {
  if (nullptr != _screen) {
    lv_obj_del(_screen);
  }
}

void Home::initStatusBar(lv_obj_t *parent, int16_t width, int16_t height) {
  static lv_style_t btsymLabelStyle;
  lv_style_init(&btsymLabelStyle);
  lv_style_set_text_font(&btsymLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_26);

  _btsymLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_btsymLabel, LV_LABEL_PART_MAIN, &btsymLabelStyle);
  lv_label_set_static_text(_btsymLabel, LV_SYMBOL_BLUETOOTH);
  lv_obj_align(_btsymLabel, nullptr, LV_ALIGN_IN_TOP_LEFT, 6, 2);

  static lv_style_t peerLabelStyle;
  lv_style_init(&peerLabelStyle);
  lv_style_set_text_font(&peerLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_20);

  _peerLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_peerLabel, LV_LABEL_PART_MAIN, &peerLabelStyle);
  onIsConnectedRelay(false);
}

void Home::initTabView(lv_obj_t *parent, int16_t width, int16_t height) {
  const int16_t statusBarHeight  = 30;
  const int16_t tabHeight        = 48;
  const int16_t tabViewHeight    = height - statusBarHeight;
  const int16_t tabContentHeight = tabViewHeight - tabHeight;

  static lv_style_t tabViewTabStyle;
  lv_style_init(&tabViewTabStyle);
  lv_style_set_text_font(&tabViewTabStyle, LV_STATE_DEFAULT, &lv_font_montserrat_16);
  lv_style_set_pad_top(&tabViewTabStyle, LV_STATE_DEFAULT, 6);
  lv_style_set_pad_bottom(&tabViewTabStyle, LV_STATE_DEFAULT, 6);
  lv_style_set_pad_left(&tabViewTabStyle, LV_STATE_DEFAULT, 0);
  lv_style_set_pad_right(&tabViewTabStyle, LV_STATE_DEFAULT, 0);

  _tabView = lv_tabview_create(parent, nullptr);
  // lv_obj_add_style(_tabView, LV_TABVIEW_PART_TAB_BTN, &tabViewButtonStyle);
  lv_obj_add_style(_tabView, LV_TABVIEW_PART_TAB_BG, &tabViewTabStyle);
  lv_obj_add_style(_tabView, LV_TABVIEW_PART_TAB_BTN, &tabViewTabStyle);
  lv_obj_set_pos(_tabView, 0, statusBarHeight);
  lv_obj_set_size(_tabView, width, tabViewHeight);
  lv_tabview_set_btns_pos(_tabView, LV_TABVIEW_TAB_POS_BOTTOM);

  _tabColor = lv_tabview_add_tab(_tabView, "Color");
  initTabColor(_tabColor, width, tabViewHeight);

  lv_obj_t *tab2 = lv_tabview_add_tab(_tabView, "Other");
  //lv_obj_t *tab3 = lv_tabview_add_tab(_tabView, "TMP");
  //lv_obj_t *tab4 = lv_tabview_add_tab(_tabView, "PRX");
  //lv_obj_t *tab5 = lv_tabview_add_tab(_tabView, "PSU");
}

void Home::initTabColor(lv_obj_t *parent, int16_t width, int16_t height) {
  // static lv_style_t colorPickerStyle;
  // lv_style_init(&colorPickerStyle);
  // lv_style_set_pad_top(&colorPickerStyle, LV_STATE_DEFAULT, 38);
  // lv_style_set_pad_bottom(&colorPickerStyle, LV_STATE_DEFAULT, 0);
  // lv_style_set_pad_left(&colorPickerStyle, LV_STATE_DEFAULT, 0);
  // lv_style_set_pad_right(&colorPickerStyle, LV_STATE_DEFAULT, 0);
  // lv_style_set_pad_inner(&colorPickerStyle, LV_STATE_DEFAULT, 0);
  // lv_style_set_radius(&colorPickerStyle, LV_STATE_DEFAULT, 4);

  _colorPicker = lv_cpicker_create(parent, nullptr);
  // lv_obj_add_style(_colorPicker, LV_CPICKER_PART_MAIN, &colorPickerStyle);
  // lv_obj_add_style(_colorPicker, LV_CPICKER_PART_KNOB, &colorPickerStyle);
  lv_cpicker_set_type(_colorPicker, LV_CPICKER_TYPE_RECT);
  lv_cpicker_set_color_mode_fixed(_colorPicker, true);
  // lv_cpicker_set_knob_colored(_colorPicker, true);
  lv_obj_set_size(_colorPicker, 200, 30);
  lv_obj_align(_colorPicker, nullptr, LV_ALIGN_IN_TOP_MID, 0, 12);

  static lv_style_t colorLabelStyle;
  lv_style_init(&colorLabelStyle);
  lv_style_set_text_font(&colorLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_22);

  _colorRedLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorRedLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorRedLabel, "R: --");
  lv_obj_align(_colorRedLabel, _colorPicker, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 16);

  _colorGreenLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorGreenLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorGreenLabel, "G: --");
  lv_obj_align(_colorGreenLabel, _colorRedLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

  _colorBlueLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorBlueLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorBlueLabel, "B: --");
  lv_obj_align(_colorBlueLabel, _colorGreenLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

  _colorXLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorXLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorXLabel, "X: --");
  lv_obj_align(_colorXLabel, _colorPicker, LV_ALIGN_OUT_BOTTOM_LEFT, width/2-20, 16);

  _colorYLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorYLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorYLabel, "Y: --");
  lv_obj_align(_colorYLabel, _colorXLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);

  _colorZLabel = lv_label_create(parent, nullptr);
  lv_obj_add_style(_colorZLabel, LV_LABEL_PART_MAIN, &colorLabelStyle);
  lv_label_set_static_text(_colorZLabel, "Z: --");
  lv_obj_align(_colorZLabel, _colorYLabel, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
}

void Home::onIsConnectedRelay(bool conn) {
  char *peerLabelText;
  lv_coord_t xOffset;
  if (conn) {
    peerLabelText = _peerAddr;
    xOffset = 10;
  } else {
    peerLabelText = __BLUETOOTH_PEER_NOT_CONNECTED_STR__;
    xOffset = 0;
  }
  lv_label_set_static_text(_peerLabel, peerLabelText);
  lv_obj_align(_peerLabel, nullptr, LV_ALIGN_IN_TOP_MID, xOffset, 6);
}

void Home::onPeerAddrRelay(uint8_t *addr) {
  snprintf(_peerAddr, __BLUETOOTH_PEER_ADDR_STRLEN__+1,
      "%02X-%02X-%02X-%02X-%02X-%02X",
      addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]
  );
}

void Home::onAccelerationRelay(Accl accl) {
  uint32_t color = accl.toArgb();

  uint8_t a = (color >> 24) & 0xFF;
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >>  8) & 0xFF;
  uint8_t b = (color >>  0) & 0xFF;

  lv_label_set_text_fmt(_colorRedLabel,   "R: %d", r);
  lv_label_set_text_fmt(_colorGreenLabel, "G: %d", g);
  lv_label_set_text_fmt(_colorBlueLabel,  "B: %d", b);

  lv_label_set_text_fmt(_colorXLabel, "X: %.3f", accl.x);
  lv_label_set_text_fmt(_colorYLabel, "Y: %.3f", accl.y);
  lv_label_set_text_fmt(_colorZLabel, "Z: %.3f", accl.z);

  lv_cpicker_set_color(_colorPicker, lv_color_make(r, g, b));
  lv_obj_invalidate(_colorPicker);
}

void Home::onAngularVelocityRelay(Gyro gyro) {

}

void Home::onMagneticFieldRelay(Mage mage) {

}

void Home::onTemperatureRelay(Temp temp) {
  // _infof("temperature = %.2f °F", temp.fahrenheit);
}

void Home::onHumidityRelay(Humi humi) {
  //_infof("humidity = %.2f %%", humi.percent);
}

void Home::onPressureRelay(Psur psur) {
  //_infof("pressure = %.2f Pas", psur.pascal);
}

void Home::onAltitudeRelay(Alti alti) {
  //_infof("altitude = %.2f m", alti.meters);
}

void Home::update(void) {
  ; // empty
}

void Home::show(void) {
  if (nullptr != _screen) {
    lv_scr_load(_screen);
  }
}

lv_obj_t *Home::colorPicker(void) {
  return _colorPicker;
}

void Home::onColorPickerEvent(lv_obj_t *obj, lv_event_t event) {
  switch (event) {
    case LV_EVENT_VALUE_CHANGED:
      _cinfof("invalidating: %p (_colorPicker = %p)", obj, _colorPicker);
      lv_obj_invalidate(obj);
      break;
  }
}
