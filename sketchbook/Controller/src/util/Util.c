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

inline int16_t interp(
    const int16_t x,
    const int16_t x1, const int16_t y1, const int16_t x2, const int16_t y2) {
  float scale = (float)(x - x1);
  float numer = (float)(y2 - x2);
  float denom = (float)(y1 - x1);
  if (fabsf(denom) < __FLOAT32_ABSTOL__) {
    denom = __FLOAT32_ABSTOL__;
  }
  return (int16_t)roundf(scale * numer / denom) + x2;
}
