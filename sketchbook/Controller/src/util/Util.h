#ifndef __UTIL_H__
#define __UTIL_H__

#include "../NeoCLUE.h"

#ifdef __cplusplus
extern "C" {
#endif

// counts the number of non-zero values in the first len elements of a.
extern inline size_t nzCount(const uint8_t a[], size_t len);

extern inline int16_t interp(
    const int16_t x,
    const int16_t x1, const int16_t y1, const int16_t x2, const int16_t y2
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __UTIL_H__
