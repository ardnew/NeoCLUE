#ifndef __NEOCLUE_H__
#define __NEOCLUE_H__

// ----------------------------------------------------------------- INCLUDES --

#include <Arduino.h>

// ------------------------------------------------------------------ DEFINES --

#define __CPU_SLEEP_DELAY__             25 // milliseconds

#define __PRINTF_DEBUG_MAX_LEN__        255 // undef to disable debug UART output

#define __FILE_NONE__                   NULL
#define __LINE_NONE__                   -1
#define __FUNCTION_NONE__               NULL

#define __CPU_HALT_DELAY__              10000 // milliseconds
#define _wait_forever \
  for(;; delay(__CPU_HALT_DELAY__)) { }

#define __BLUETOOTH_NAME__              "NeoCLUE-Controller"

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

#define _sizeof_array(x) (sizeof(x) / sizeof(*(x)))

#if __PRINTF_DEBUG_MAX_LEN__
  #define __PRINTF_DEBUG__
  #define _wait_for_serial(baud) \
      Serial.begin(baud); while (!Serial) { delay(__CPU_SLEEP_DELAY__); }
#else
  #define _wait_for_serial(baud) \
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
      ( (__FILE_NONE__     != (filename))    &&           \
        (__LINE_NONE__     != (lineno))      &&           \
        (__FUNCTION_NONE__ != (funcname)) )

#endif // __NEOCLUE_H__
