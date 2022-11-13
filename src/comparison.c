// SPDX-License-Identifier: GPL-2.0-only

#include "krall/comparison.h"
#include <stdint.h>

int uint32_t_comparison(const void *lhs, const void *rhs) {
  if (*(uint32_t *)lhs > *(uint32_t *)rhs) {
    return 1;
  }
  if (*(uint32_t *)lhs < *(uint32_t *)rhs) {
    return -1;
  }
  return 0;
}
