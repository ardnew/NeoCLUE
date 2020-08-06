#ifndef __VIEW_H__
#define __VIEW_H__

class View {
private:
protected:
  View(void) {
    ; // invalid. this class is purely virtual
  }

public:
  virtual ~View(void) {
    ; // empty. definition required.
  }

  enum class Kind { None, Home, Scan };
  virtual Kind kind(void) = 0;

  virtual void update(void) = 0;
};

#endif // __VIEW_H__
