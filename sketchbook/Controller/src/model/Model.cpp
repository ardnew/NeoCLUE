#include "Model.h"
#include "../util/Util.h"

Model *model = new Model();

Model::Model(void):
    _isConnected(false),
    _isConnectedRelay(new Relay<bool>()),
    _peerAddrRelay(new Relay<uint8_t *>()),
    _acceleration(),
    _accelerationRelay(new Relay<Accl>()),
    _angularVelocity(),
    _angularVelocityRelay(new Relay<Gyro>()),
    _magneticField(),
    _magneticFieldRelay(new Relay<Mage>()) {
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
