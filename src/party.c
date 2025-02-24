// SPDX-License-Identifier: GPL-2.0-only

#include "krall/gameplay/party.h"

uint32_t total_hit_points_of_party(character_sheet *party) {
  uint32_t sum = 0;

  for (size_t i = 0; i < PARTY_SIZE; i++) {
    const int32_t points = (party + i)->current_hit_points;

    // conversion - No negative values will be converted, so no sign change will
    // occur from the cast.
    sum = sum + (unsigned)((points < 0) ? 0 : points);
  }

  return sum;
}

