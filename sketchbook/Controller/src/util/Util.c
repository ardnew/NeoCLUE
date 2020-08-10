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
