#ifndef __UTIL_H__
#define __UTIL_H__

// #include <functional>

#include "../NeoCLUE.h"

#ifdef __cplusplus
extern "C" {
#endif

// counts the number of non-zero values in the first len elements of a.
extern inline size_t nzCount(const uint8_t a[], size_t len);

extern inline int32_t interp(
    const int32_t x,
    const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2
);

#ifdef __cplusplus
} // extern "C"
#endif

// typedef  std::function<bool (const timespan_t)> timespan_predicate_t;

// timespan_predicate_t hasElapsed(timespan_t now);

#endif // __UTIL_H__
