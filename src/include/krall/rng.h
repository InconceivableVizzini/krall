// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include <stdint.h>

void initialize_random_number_generator(void);
uint32_t random_u32(void);

static inline uint32_t roll_one_die(uint32_t sides) {
  return (random_u32() % sides) + 1;
}

#define roll_some_dice(m, n)                                                   \
  uint32_t some_dice_rolls[m];                                                 \
  for (size_t i = 0; i < m; i++) {                                             \
    some_dice_rolls[i] = roll_one_die(n);                                      \
  }
