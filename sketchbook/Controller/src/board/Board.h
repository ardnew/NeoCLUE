#ifndef __BOARD_H__
#define __BOARD_H__

// Project
#include "../NeoCLUE.h"
#include "../model/Model.h"
#include "../view/View.h"
#include "../view/home/Home.h"
#include "../view/scan/Scan.h"

class Board {
private:
protected:
  Board(void) { /* empty. this class is purely virtual (no instantiation) */ }

public:
  enum class InitError { None, LCD, BLE, SEN };

  virtual InitError begin(void) = 0;
  virtual void update(void) = 0;
};

extern Board *board;

#endif // __BOARD_H__
