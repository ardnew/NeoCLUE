#ifndef __NEOCLUE_H__
#define __NEOCLUE_H__

// ----------------------------------------------------------------- INCLUDES --

#include <Arduino.h>

// ------------------------------------------------------------------ DEFINES --

#define __CPU_SLEEP_DELAY__             1 // main loop delay (per iteration)

#define __SERIAL_DEBUG_BAUD_RATE__      115200
#define __SERIAL_BOOT_TIMEOUT__         5000 // milliseconds to wait before proceding with bootup
#define __PRINTF_DEBUG_MAX_LEN__        255 // undef to disable debug UART output

#define __FLOAT32_ABSTOL__              5.0e-6  // 32-bit
#define __FLOAT64_ABSTOL__              5.0e-14 // 64-bit

#define __FILE_NONE__                   NULL
#define __LINE_NONE__                   -1
#define __FUNCTION_NONE__               NULL

#define __BLUETOOTH_NAME__              "NeoCLUE\0"
#define __BLEUTOOTH_PEER_ADDR_SIZE__    6
#define __BLUETOOTH_PEER_ADDR_STRLEN__                                         \
    ( (2*(__BLEUTOOTH_PEER_ADDR_SIZE__)) +                                     \
      ((__BLEUTOOTH_PEER_ADDR_SIZE__)-1) )

#define __TIMESPAN_MAX__                ((timespan_t)0xFFFFFFFF)

// ----------------------------------------------------------------- TYPEDEFS --

typedef unsigned long timespan_t; // storage for arduino's millis()

typedef enum {
  ilNONE = -1,
  ilInfo,    // = 0
  ilWarn,    // = 1
  ilError,   // = 2
  ilContext, // = 3
  ilCOUNT    // = 4
} info_level_t;

// ----------------------------------------------------------- FUNCTION DECLS --

void print(info_level_t level, const char *filename, int lineno, const char *funcname, const char *fmt, ...);

// ------------------------------------------------------------------- MACROS --

#define _halt { for(;;) { yield(); } }

#define _sizeof_array(x) (sizeof(x) / sizeof(*(x)))

#define _unused(x) ; ((void)(x)) ;

// if C++17 is available, this should be replaced with std::invoke(). until
// then, however, use this definition when calling ANY member function.
#define _invoke(obj, mth) ((obj).*(mth))

#if __PRINTF_DEBUG_MAX_LEN__
  #define __PRINTF_DEBUG__
  #define _wait_for_serial(baud, timeout) \
      for (Serial.begin(baud); !Serial && (millis() < (timeout)); delay(__CPU_SLEEP_DELAY__));
#else
  #define _wait_for_serial(baud, timeout) \
      /* debug code omitted */
#endif

#define _cstamp           print(ilContext, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL, NULL)
#define _cinfof(fmt, ...) print(ilInfo, __FILE__, __LINE__, __PRETTY_FUNCTION__, fmt, __VA_ARGS__)
#define _cwarnf(fmt, ...) print(ilWarn, __FILE__, __LINE__, __PRETTY_FUNCTION__, fmt, __VA_ARGS__)
#define _cerrf(fmt, ...)  print(ilError, __FILE__, __LINE__, __PRETTY_FUNCTION__, fmt, __VA_ARGS__)

#define _infof(fmt, ...) print(ilInfo, __FILE_NONE__, __LINE_NONE__, __FUNCTION_NONE__, fmt, __VA_ARGS__)
#define _warnf(fmt, ...) print(ilWarn, __FILE_NONE__, __LINE_NONE__, __FUNCTION_NONE__, fmt, __VA_ARGS__)
#define _errf(fmt, ...)  print(ilError, __FILE_NONE__, __LINE_NONE__, __FUNCTION_NONE__, fmt, __VA_ARGS__)

#define _should_print_context(filename, lineno, funcname) \
    ( (__FILE_NONE__     != (filename))    &&             \
      (__LINE_NONE__     != (lineno))      &&             \
      (__FUNCTION_NONE__ != (funcname)) )

#endif // __NEOCLUE_H__
