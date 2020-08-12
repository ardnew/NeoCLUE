#ifndef __RELAY_H__
#define __RELAY_H__

#include <functional>

// Project
#include "../util/LinkedList.h"

template <typename T>
class Relay {
private:
  LinkedList<std::function<void(T)>> *_subscription;

protected:
public:
  Relay(void);
  ~Relay(void);

  template <class C>
  bool subscribe(C * const object, void(C::* const method)(T));
  bool subscribe(std::function<void(T)> callback);
  void unsubscribeAll(void);
  void send(T data);
};

template <typename T>
Relay<T>::Relay(void):
    _subscription(new LinkedList<std::function<void(T)>>()) {
  ; // empty
}

template <typename T>
Relay<T>::~Relay(void) {
  if (nullptr != _subscription) {
    delete _subscription;
  }
}

template <typename T>
template <class C>
bool Relay<T>::subscribe(C * const object, void(C::* const method)(T)) {
  using namespace std::placeholders; {
    return subscribe(std::bind(method, object, _1));
  }
}

template <typename T>
bool Relay<T>::subscribe(std::function<void(T)> callback) {
  if (nullptr != _subscription && nullptr != callback) {
    return _subscription->add(callback);
  }
  return false;
}

template <typename T>
void Relay<T>::unsubscribeAll(void) {
  if (nullptr != _subscription) {
    _subscription->clear();
  }
}

template <typename T>
void Relay<T>::send(T data) {
  if (nullptr != _subscription) {
    for (int i = 0; i < _subscription->size(); ++i) {
      _subscription->get(i)(data);
    }
  }
}

#endif // __RELAY_H__
