// SPDX-License-Identifier: GPL-2.0-only

#include "krall/gameplay/game.h"

void initialize_gameplay(game *the_game) {
  for (size_t i = 0; i < 5; i++) {
    the_game->party[i] = create_random_playable_character();
  }
  
  the_game->party[0].current_hit_points = 2;
}

bool update_gameplay(game *the_game) {
  (void)the_game;
  return true;
}
