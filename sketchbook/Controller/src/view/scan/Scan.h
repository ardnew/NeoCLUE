#ifndef __SCAN_H__
#define __SCAN_H__

#include "../View.h"

class Scan: public View {
private:
protected:
public:
  Scan(void);
  ~Scan(void);

  View::Kind kind(void) { return View::Kind::Scan; }

  void update(void);
};

#endif // __SCAN_H__
