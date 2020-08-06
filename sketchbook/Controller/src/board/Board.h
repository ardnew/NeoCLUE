#ifndef __BOARD_H__
#define __BOARD_H__

class Board {
private:
protected:
public:
  enum class InitError { None, LCD, BLE };

  Board(void) {
    ; // empty
  }

  virtual InitError begin(void) =0;
  virtual void update(void) =0;
};

extern Board *board;

#endif // __BOARD_H__
