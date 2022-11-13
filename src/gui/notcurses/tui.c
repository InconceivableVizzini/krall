// SPDX-License-Identifier: GPL-2.0-only

#include "tui.h"
#include <stdlib.h>

static struct notcurses *notcurses;

void initialize_gui(void) {
  struct notcurses_options options = {0};
  notcurses = notcurses_init(&options, NULL);
  if (!notcurses || !notcurses_canopen_images(notcurses)) {
    exit(EXIT_FAILURE);
  }
}

enum gui_top_level_frames {
  CHARACTER_SHEET_FRAME,
  MAP_FRAME,
  GAMEPLAY_FRAME,
  JOURNAL_FRAME,
  NUMBER_OF_TOP_LEVEL_FRAMES
};
typedef enum gui_top_level_frames gui_top_level_frames;

enum gui_frame_visuals { GAME, B, NUMBER_OF_GUI_FRAME_VISUALS };
typedef enum gui_frame_visuals gui_frame_visuals;

struct gui_frame {
  struct ncvisual *ncvisual[NUMBER_OF_GUI_FRAME_VISUALS];
};
typedef struct gui_frame gui_frame;

bool update_gui_events(game *the_game) {
  update_gameplay(the_game);

  ncinput notcurses_input;
  uint32_t id;
  while ((id = notcurses_get_blocking(notcurses, &notcurses_input)) !=
         (uint32_t)-1) {
    if (id == 0) {
      continue; // timeout waiting for input
    }

    if (id == NCKEY_EOF || id == NCKEY_ESC) {
      return false;
    }

    if (id == NCKEY_RESIZE) {
      unsigned int height, width;
      notcurses_refresh(notcurses, &height, &width);
    }

    break;
  }

  notcurses_render(notcurses);
  return true;
}

void deinitialize_gui(void) {
  notcurses_render(notcurses);
  notcurses_stop(notcurses);
}
