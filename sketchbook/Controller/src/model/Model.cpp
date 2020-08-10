#include "Model.h"
#include "../util/Util.h"

Model *model = new Model();

Model::Model(void):
  _isConnected(false),
  _isConnectedRelay(new Relay<bool>()),
  _peerAddrRelay(new Relay<uint8_t *>()) {
  setPeerAddr(nullptr);
}

void Model::clearRelays(void) {
  if (nullptr != _isConnectedRelay) {
    _isConnectedRelay->unsubscribeAll();
  }
  if (nullptr != _peerAddrRelay) {
    _peerAddrRelay->unsubscribeAll();
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
