#include "src/NeoCLUE.h"

#ifdef ARDUINO_NRF52840_ITSYBITSY
#include "src/board/itsybitsy/ItsyBitsy.h"
#endif

bool setupBoard(void) {
  Board::InitError err = board->begin();
  switch (err) {
    case Board::InitError::None: {
      return true;
    }
    case Board::InitError::PIX: {
      _cerrf("%s", "failed to initialize LED strip interface");
      return false;
    }
    case Board::InitError::BLE: {
      _cerrf("%s", "failed to initialize Bluetooth (LE) module");
      return false;
    }
    default: {
      _cerrf("%s (%d)", "failed to initialize", err);
      return false;
    }
  }
}

void setup(void) {
  _wait_for_serial(__SERIAL_DEBUG_BAUD_RATE__, __SERIAL_BOOT_TIMEOUT__);
  if (!setupBoard()) _halt;
}

void loop(void) {
  board->update();
  delay(__CPU_SLEEP_DELAY__);
}

void print(info_level_t level, const char *filename, int lineno, const char *funcname, const char *fmt, ...) {
#ifdef __PRINTF_DEBUG__

  static const char *debug_level_prefix[ilCOUNT] = {
    "[ ] ", "[*] ", "[!] ", "[=] "
  };
  static char buff[__PRINTF_DEBUG_MAX_LEN__ + 1] = { 0 };
  static int count = 0; ++count;

  if (_should_print_context(filename, lineno, funcname)) {
    memset(buff, 0, __PRINTF_DEBUG_MAX_LEN__ + 1);
    snprintf(buff, __PRINTF_DEBUG_MAX_LEN__, "%d~%s@%d:%s", count, filename, lineno, funcname);
    Serial.print(debug_level_prefix[level]);
    Serial.println(buff);
  }

  if (NULL != fmt) {
    va_list arg;
    va_start(arg, fmt);
    memset(buff, 0, __PRINTF_DEBUG_MAX_LEN__ + 1);
    vsnprintf(buff, __PRINTF_DEBUG_MAX_LEN__, fmt, arg);
    va_end(arg);
    Serial.print(debug_level_prefix[level]);
    Serial.println(buff);
  }

#else
  (void)level;
  (void)filename;
  (void)lineno;
  (void)funcname;
  (void)fmt;
#endif
}
