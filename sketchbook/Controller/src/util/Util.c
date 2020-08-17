#include "Util.h"

// counts the number of non-zero values in the first len elements of a.
inline size_t nzCount(const uint8_t a[], size_t len) {
  size_t count = 0;
  if (NULL != a) {
    for (int i = 0; i < len; ++i) {
      if (0 != a[i]) { ++count; }
    }
  }
  return  count;
}

inline int32_t interp(
    const int32_t x,
    const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2) {
  float scale = (float)(x - x1);
  float numer = (float)(y2 - x2);
  float denom = (float)(y1 - x1);
  if (fabsf(denom) < __FLOAT32_ABSTOL__) {
    denom = __FLOAT32_ABSTOL__;
  }
  return (int32_t)lroundf(scale * numer / denom) + x2;
}
