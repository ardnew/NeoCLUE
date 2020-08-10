#include "Home.h"

#define __BLUETOOTH_PEER_NOT_CONNECTED_STR__  "Scanning...\0"

Home::Home(void):
  _screen(lv_obj_create(NULL, NULL)),
  _btsymLabel(nullptr),
  _peerLabel(nullptr) {
  memset(_peerAddr, 0, __BLUETOOTH_PEER_ADDR_STRLEN__);
}

Home::Home(const uint16_t width, const uint16_t height):
  Home() {

  lv_obj_set_pos(_screen, 0, 0);
  lv_obj_set_size(_screen, width, height);

  initStatusBar(_screen, width, height);
  initTabView(_screen, width, height);
  initAcc(_screen, width, height);

  model->clearRelays();
  model->isConnectedRelay()->subscribe(this, &Home::onIsConnectedRelay);
  model->peerAddrRelay()->subscribe(this, &Home::onPeerAddrRelay);
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

  _btsymLabel = lv_label_create(parent, NULL);
  lv_obj_add_style(_btsymLabel, LV_LABEL_PART_MAIN, &btsymLabelStyle);
  lv_label_set_static_text(_btsymLabel, LV_SYMBOL_BLUETOOTH);
  lv_obj_align(_btsymLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 2, 2);

  static lv_style_t peerLabelStyle;
  lv_style_init(&peerLabelStyle);
  lv_style_set_text_font(&peerLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_20);

  _peerLabel = lv_label_create(parent, NULL);
  lv_obj_add_style(_peerLabel, LV_LABEL_PART_MAIN, &peerLabelStyle);
  onIsConnectedRelay(false);
}

void Home::initTabView(lv_obj_t *parent, int16_t width, int16_t height) {
  static lv_style_t tabViewButtonStyle;
  lv_style_init(&tabViewButtonStyle);
  lv_style_set_text_font(&tabViewButtonStyle, LV_STATE_DEFAULT, &lv_font_montserrat_16);

  _tabView = lv_tabview_create(parent, NULL);
  lv_obj_add_style(_tabView, LV_TABVIEW_PART_TAB_BTN, &tabViewButtonStyle);
  lv_obj_set_pos(_tabView, 0, 30);
  lv_obj_set_size(_tabView, width, height-30);
  lv_tabview_set_btns_pos(_tabView, LV_TABVIEW_TAB_POS_BOTTOM);

  /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
  lv_obj_t *tab1 = lv_tabview_add_tab(_tabView, "ACC");
  lv_obj_t *tab2 = lv_tabview_add_tab(_tabView, "MAG");
  lv_obj_t *tab3 = lv_tabview_add_tab(_tabView, "TMP");
  lv_obj_t *tab4 = lv_tabview_add_tab(_tabView, "PRX");
  lv_obj_t *tab5 = lv_tabview_add_tab(_tabView, "PSU");
}

void Home::initAcc(lv_obj_t *parent, int16_t width, int16_t height) {

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
  lv_obj_align(_peerLabel, NULL, LV_ALIGN_IN_TOP_MID, xOffset, 6);
}

void Home::onPeerAddrRelay(uint8_t *addr) {
  snprintf(_peerAddr, __BLUETOOTH_PEER_ADDR_STRLEN__+1,
    "%02X-%02X-%02X-%02X-%02X-%02X",
    addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]
  );
}

void Home::update(void) {
  ; // empty
}

void Home::show(void) {
  if (nullptr != _screen) {
    lv_scr_load(_screen);
  }
}
