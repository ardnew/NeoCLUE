#ifndef __CLUE_H__
#define __CLUE_H__

#include "../../NeoCLUE.h"
#include "../Board.h"

#include "periph/Lcd.h"
#include "periph/Ble.h"

class Clue: public Board {
private:
protected:
  Lcd *_lcd;
  Ble *_ble;

public:
  Clue(void);

  Lcd *lcd(void) { return _lcd; }
  Ble *ble(void) { return _ble; }

  Board::InitError begin(void);
  void update(void);
};

#endif // __CLUE_H__
