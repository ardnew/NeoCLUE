#ifndef __VIEW_H__
#define __VIEW_H__

// LCD Graphics
#include <lvgl.h>

// Project
#include "../NeoCLUE.h"
#include "../model/Model.h"

class View {
private:
protected:
  View(void) { /* empty. this class is purely virtual (no instantiation) */ }

public:
  virtual ~View(void) { /* empty. public definition required. */ }

  enum class Kind { None, Home, Scan };
  virtual Kind kind(void) = 0;

  virtual void update(void) = 0;
  virtual void show(void) = 0;
};

#endif // __VIEW_H__
