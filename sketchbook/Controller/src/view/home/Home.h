#ifndef __HOME_H__
#define __HOME_H__

#include "../View.h"

class Home: public View {
private:
  char _peerAddr[__BLUETOOTH_PEER_ADDR_STRLEN__];

  void initStatusBar(lv_obj_t *parent, int16_t width, int16_t height);
  void initTabView(lv_obj_t *parent, int16_t width, int16_t height);
  void initTabColor(lv_obj_t *parent, int16_t width, int16_t height);

protected:
  lv_obj_t *_screen;
  lv_obj_t *_btsymLabel;
  lv_obj_t *_peerLabel;
  lv_obj_t *_tabView;
  lv_obj_t *_tabColor;
  lv_obj_t *_colorPicker;
  lv_obj_t *_colorRedLabel;
  lv_obj_t *_colorGreenLabel;
  lv_obj_t *_colorBlueLabel;
  lv_obj_t *_colorXLabel;
  lv_obj_t *_colorYLabel;
  lv_obj_t *_colorZLabel;

public:
  Home(void);
  Home(const uint16_t width, const uint16_t height);
  ~Home(void);

  View::Kind kind(void) { return View::Kind::Home; }

  void onIsConnectedRelay(bool conn);
  void onPeerAddrRelay(uint8_t *addr);
  void onAccelerationRelay(Accl accl);
  void onAngularVelocityRelay(Gyro gyro);
  void onMagneticFieldRelay(Mage mage);
  void onTemperatureRelay(Temp temp);
  void onHumidityRelay(Humi humi);
  void onPressureRelay(Psur psur);
  void onAltitudeRelay(Alti alti);

  void update(void);
  void show(void);

  lv_obj_t *colorPicker(void);
  void onColorPickerEvent(lv_obj_t *obj, lv_event_t event);
};

#endif // __HOME_H__
