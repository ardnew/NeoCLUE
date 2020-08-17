#ifndef __MODEL_H__
#define __MODEL_H__

// Project
#include "../NeoCLUE.h"
#include "../msg/Relay.h"
#include "Data.h"

class Model {
private:
  bool _isConnected;
  uint8_t _peerAddr[__BLEUTOOTH_PEER_ADDR_SIZE__];
  uint16_t _numPixels;
  uint16_t _colorOrder;
  uint16_t _pixelType;
  Accl _acceleration;
  Gyro _angularVelocity;
  Mage _magneticField;
  Temp _temperature;
  Humi _humidity;
  Psur _pressure;
  Alti _altitude;

  Relay<bool> *_isConnectedRelay;
  Relay<uint8_t *> *_peerAddrRelay;
  Relay<Accl> *_accelerationRelay;
  Relay<Gyro> *_angularVelocityRelay;
  Relay<Mage> *_magneticFieldRelay;
  Relay<Temp> *_temperatureRelay;
  Relay<Humi> *_humidityRelay;
  Relay<Psur> *_pressureRelay;
  Relay<Alti> *_altitudeRelay;

protected:
public:
  Model(void);

  void clearRelays(void);

  // only use for managing subscriptions. do not send data directly to these.
  // instead, use the methods defined on the model below, which do proper sanity
  // checking and stuff before relaying data on to subscribers.
  Relay<bool> *isConnectedRelay(void) { return _isConnectedRelay; }
  Relay<uint8_t *> *peerAddrRelay(void) { return _peerAddrRelay; }
  Relay<Accl> *accelerationRelay(void) { return _accelerationRelay; }
  Relay<Gyro> *angularVelocityRelay(void) { return _angularVelocityRelay; }
  Relay<Mage> *magneticFieldRelay(void) { return _magneticFieldRelay; }
  Relay<Temp> *temperatureRelay(void) { return _temperatureRelay; }
  Relay<Humi> *humidityRelay(void) { return _humidityRelay; }
  Relay<Psur> *pressureRelay(void) { return _pressureRelay; }
  Relay<Alti> *altitudeRelay(void) { return _altitudeRelay; }

  void setIsConnected(bool conn);
  bool isConnected(void);

  void setPeerAddr(const uint8_t addr[]);
  uint8_t *peerAddr(void);

  void setNumPixels(const uint16_t numPixels);
  uint16_t numPixels(void);
  void setColorOrder(const uint16_t colorOrder);
  uint16_t colorOrder(void);
  void setPixelType(const uint16_t pixelType);
  uint16_t pixelType(void);

  void setAcceleration(const Accl accl);
  Accl acceleration(void);

  void setAngularVelocity(const Gyro gyro);
  Gyro angularVelocity(void);

  void setMagneticField(const Mage mage);
  Mage magneticField(void);

  void setTemperature(const Temp temp);
  Temp temperature(void);

  void setHumidity(const Humi humi);
  Humi humidity(void);

  void setPressure(const Psur psur);
  Psur pressure(void);

  void setAltitude(const Alti alti);
  Alti altitude(void);
};

extern Model *model;

#endif // __MODEL_H__
