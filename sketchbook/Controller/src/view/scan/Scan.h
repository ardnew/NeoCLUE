#ifndef __SCAN_H__
#define __SCAN_H__

#include "../View.h"

class Scan: public View {
private:
protected:
  lv_obj_t *_screen;

public:
  Scan(void);
  Scan(const uint16_t width, const uint16_t height);
  ~Scan(void);

  View::Kind kind(void) { return View::Kind::Scan; }

  void update(void);
  void show(void);
};

#endif // __SCAN_H__
