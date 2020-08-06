#ifndef __BOARD_H__
#define __BOARD_H__

class Board {
private:
protected:
  Board(void) {
    ; // invalid. this class is purely virtual
  }

public:
  enum class InitError { None, BLE };

  virtual InitError begin(void) = 0;
  virtual void update(void) = 0;
};

extern Board *board;

#endif // __BOARD_H__
