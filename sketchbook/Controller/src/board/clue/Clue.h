#ifndef __CLUE_H__
#define __CLUE_H__

#include "../Board.h"

#include "periph/Lcd.h"
#include "periph/Ble.h"
#include "periph/Sen.h"

class Clue: public Board {
private:
protected:
  Lcd *_lcd;
  Ble *_ble;
  Sen *_sen;

public:
  Clue(void);

  Lcd *lcd(void) { return _lcd; }
  Ble *ble(void) { return _ble; }
  Sen *sen(void) { return _sen; }

  Board::InitError begin(void);
  void update(void);
};

#endif // __CLUE_H__
