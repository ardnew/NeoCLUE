#include "Model.h"
#include "../util/Util.h"

Model *model = new Model();

Model::Model(void):
    _isConnected(false),
    _isConnectedRelay(new Relay<bool>()),
    _peerAddrRelay(new Relay<uint8_t *>()),
    _numPixels(0),
    _colorOrder(0),
    _pixelType(0),
    _acceleration(),
    _accelerationRelay(new Relay<Accl>()),
    _angularVelocity(),
    _angularVelocityRelay(new Relay<Gyro>()),
    _magneticField(),
    _magneticFieldRelay(new Relay<Mage>()),
    _temperature(),
    _temperatureRelay(new Relay<Temp>()),
    _humidity(),
    _humidityRelay(new Relay<Humi>()),
    _pressure(),
    _pressureRelay(new Relay<Psur>()),
    _altitude(),
    _altitudeRelay(new Relay<Alti>()) {
  setPeerAddr(nullptr);
}

void Model::clearRelays(void) {
  if (nullptr != _isConnectedRelay) {
    _isConnectedRelay->unsubscribeAll();
  }
  if (nullptr != _peerAddrRelay) {
    _peerAddrRelay->unsubscribeAll();
  }
  if (nullptr != _accelerationRelay) {
    _accelerationRelay->unsubscribeAll();
  }
  if (nullptr != _angularVelocityRelay) {
    _angularVelocityRelay->unsubscribeAll();
  }
  if (nullptr != _magneticFieldRelay) {
    _magneticFieldRelay->unsubscribeAll();
  }
  if (nullptr != _temperatureRelay) {
    _temperatureRelay->unsubscribeAll();
  }
  if (nullptr != _humidityRelay) {
    _humidityRelay->unsubscribeAll();
  }
  if (nullptr != _pressureRelay) {
    _pressureRelay->unsubscribeAll();
  }
  if (nullptr != _altitudeRelay) {
    _altitudeRelay->unsubscribeAll();
  }
}

void Model::setIsConnected(bool conn) {
  _isConnected = conn;
  _isConnectedRelay->send(isConnected());
}

bool Model::isConnected(void) {
  return _isConnected;
}

void Model::setPeerAddr(const uint8_t addr[]) {
  size_t count = nzCount(addr, __BLEUTOOTH_PEER_ADDR_SIZE__);
  if (count > 0) {
    (void)memcpy(_peerAddr, addr, __BLEUTOOTH_PEER_ADDR_SIZE__);
  } else {
    (void)memset(_peerAddr, 0, __BLEUTOOTH_PEER_ADDR_SIZE__);
  }
  _peerAddrRelay->send(peerAddr());
}

uint8_t *Model::peerAddr(void) {
  return _isConnected ? _peerAddr : nullptr;
}

void Model::setNumPixels(const uint16_t numPixels) {
  _numPixels = numPixels;
}

uint16_t Model::numPixels(void) {
  return _numPixels;
}

void Model::setColorOrder(const uint16_t colorOrder) {
  _colorOrder = colorOrder;
}

uint16_t Model::colorOrder(void) {
  return _colorOrder;
}

void Model::setPixelType(const uint16_t pixelType) {
  _pixelType = pixelType;
}

uint16_t Model::pixelType(void) {
  return _pixelType;
}

void Model::setAcceleration(const Accl accl) {
  _acceleration = accl;
  _accelerationRelay->send(acceleration());
}

Accl Model::acceleration(void) {
  return _acceleration;
}

void Model::setAngularVelocity(const Gyro gyro) {
  _angularVelocity = gyro;
  _angularVelocityRelay->send(angularVelocity());
}

Gyro Model::angularVelocity(void) {
  return _angularVelocity;
}

void Model::setMagneticField(const Mage mage) {
  _magneticField = mage;
  _magneticFieldRelay->send(magneticField());
}

Mage Model::magneticField(void) {
  return _magneticField;
}

void Model::setTemperature(const Temp temp) {
  _temperature = temp;
  _temperatureRelay->send(temperature());
}

Temp Model::temperature(void) {
  return _temperature;
}

void Model::setHumidity(const Humi humi) {
  _humidity = humi;
  _humidityRelay->send(humidity());
}

Humi Model::humidity(void) {
  return _humidity;
}

void Model::setPressure(const Psur psur) {
  _pressure = psur;
  _pressureRelay->send(pressure());
}

Psur Model::pressure(void) {
  return _pressure;
}

void Model::setAltitude(const Alti alti) {
  _altitude = alti;
  _altitudeRelay->send(altitude());
}

Alti Model::altitude(void) {
  return _altitude;
}
