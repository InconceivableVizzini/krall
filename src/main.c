// SPDX-License-Identifier: GPL-2.0-only

#include <mimalloc.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "characters/strings.h"
#include "krall/gameplay/game.h"
#include "krall/gameplay/party.h"
#include "krall/rng.h"

#ifdef TUI
#include "tui.h"
#endif

static allocator memory_allocator = {
    .management_routines = {.allocate = &mi_malloc,
                            .reallocate = &mi_realloc,
                            .deallocate = &mi_free}};

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  (void)memory_allocator;

  initialize_random_number_generator();

  initialize_gui();

  game the_game = {0};

  initialize_gameplay(&the_game);

  while (update_gui_events(&the_game));

  deinitialize_gui();

  return EXIT_SUCCESS;
}
