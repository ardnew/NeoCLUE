#ifndef __HOME_H__
#define __HOME_H__

#include "../View.h"

class Home: public View {
private:
protected:
public:
  Home(void);
  ~Home(void);

  View::Kind kind(void) { return View::Kind::Home; }

  void update(void);
};

#endif // __HOME_H__
