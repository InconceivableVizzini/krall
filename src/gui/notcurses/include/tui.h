// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "krall/gameplay/game.h"
#include <notcurses/notcurses.h>

void initialize_gui(void);
bool update_gui_events(game *the_game);
void deinitialize_gui(void);
