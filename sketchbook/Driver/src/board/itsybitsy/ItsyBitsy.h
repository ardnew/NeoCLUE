#ifndef __ITSYBITSY_H__
#define __ITSYBITSY_H__

#include "../Board.h"

#include "periph/Pix.h"
#include "periph/Ble.h"

class ItsyBitsy: public Board {
private:
protected:
  Pix *_pix;
  Ble *_ble;

public:
  ItsyBitsy(void);

  Pix *pix(void) { return _pix; }
  Ble *ble(void) { return _ble; }

  Board::InitError begin(void);
  void update(void);
};

#endif // __ITSYBITSY_H__
