#ifndef __HOME_H__
#define __HOME_H__

#include "../View.h"

class Home: public View {
private:
  char _peerAddr[__BLUETOOTH_PEER_ADDR_STRLEN__];

  void initStatusBar(lv_obj_t *parent, int16_t width, int16_t height);
  void initTabView(lv_obj_t *parent, int16_t width, int16_t height);
  void initAcc(lv_obj_t *parent, int16_t width, int16_t height);

protected:
  lv_obj_t *_screen;
  lv_obj_t *_btsymLabel;
  lv_obj_t *_peerLabel;
  lv_obj_t *_tabView;

public:
  Home(void);
  Home(const uint16_t width, const uint16_t height);
  ~Home(void);

  View::Kind kind(void) { return View::Kind::Home; }

  void onIsConnectedRelay(bool conn);
  void onPeerAddrRelay(uint8_t *addr);

  void update(void);
  void show(void);
};

#endif // __HOME_H__
