#ifndef __MODEL_H__
#define __MODEL_H__

// Project
#include "../NeoCLUE.h"
#include "../msg/Relay.h"

class Model {
private:
  bool _isConnected;
  uint8_t _peerAddr[__BLEUTOOTH_PEER_ADDR_SIZE__];

  Relay<bool> *_isConnectedRelay;
  Relay<uint8_t *> *_peerAddrRelay;

protected:
public:
  Model(void);

  void clearRelays(void);

  // only use for managing subscriptions. do not send data directly to these.
  // instead, use the methods defined on the model below, which do proper sanity
  // checking and stuff before relaying data on to subscribers.
  Relay<bool> *isConnectedRelay(void) { return _isConnectedRelay; }
  Relay<uint8_t *> *peerAddrRelay(void) { return _peerAddrRelay; }

  void setIsConnected(bool conn);
  bool isConnected(void);

  void setPeerAddr(const uint8_t addr[]);
  uint8_t *peerAddr(void);
};

extern Model *model;

#endif // __MODEL_H__
