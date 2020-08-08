#ifndef __ITSYBITSY_H__
#define __ITSYBITSY_H__

#include "../../NeoCLUE.h"
#include "../Board.h"

#include "periph/Led.h"
#include "periph/Ble.h"

class ItsyBitsy: public Board {
private:
protected:
  Led *_led;
  Ble *_ble;

public:
  ItsyBitsy(void);

  Led *led(void) { return _led; }
  Ble *ble(void) { return _ble; }

  Board::InitError begin(void);
  void update(void);
};

#endif // __ITSYBITSY_H__
