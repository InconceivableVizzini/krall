// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "krall/character_sheet.h"
#include "krall/gameplay/party.h"

struct game {
  character_sheet party[PARTY_SIZE];
};
typedef struct game game;

void initialize_gameplay(game *the_game);
bool update_gameplay(game *the_game);
