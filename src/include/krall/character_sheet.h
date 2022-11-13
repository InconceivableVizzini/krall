// SPDX-License-Identifier: GPL-2.0-only
#pragma once

#include "characters/strings.h"
#include "math.h"

enum character_sheet_saving_throws {
  STRENGTH_THROW,
  DEXTERITY_THROW,
  CONSTITUTION_THROW,
  INTELLIGENCE_THROW,
  WISDOM_THROW,
  CHARISMA_THROW,
  NUMBER_OF_SAVING_THROWS
};
typedef enum character_sheet_saving_throws saving_throws;

enum character_sheet_character_classes {
  ROGUE_CLASS,
  BARBARIAN_CLASS,
  RANGER_CLASS,
  MONK_CLASS,
  NUMBER_OF_CHARACTER_CLASSES
};
typedef enum character_sheet_character_classes character_classes;

enum character_sheet_races {
  DRAGONBORN_RACE,
  DROW_RACE,
  DWARF_RACE,
  ELF_RACE,
  GNOME_RACE,
  HALF_ELF_RACE,
  HALFLING_RACE,
  HALF_ORC_RACE,
  HUMAN_RACE,
  TIEFLING_RACE,
  ORC_RACE,
  LEONIN_RACE,
  SATYR_RACE,
  OWLIN_RACE,
  SVIRFNEBLIN_RACE,
  DUERGAR_RACE,
  FIRBOLG_RACE,
  GOBLIN_RACE,
  GOLIATH_RACE,
  KOBOLD_RACE,
  TORTLE_RACE,
  YUAN_TI_RACE,
  NUMBER_OF_RACES
};
typedef enum character_sheet_races races;

enum character_sheet_alignments {
  CRUSADER_ALIGNMENT,
  BENEFACTOR_ALIGNMENT,
  REBEL_ALIGNMENT,
  JUDGE_ALIGNMENT,
  FULCRUM_ALIGNMENT,
  FREE_SPIRIT_ALIGNMENT,
  DOMINATOR_ALIGNMENT,
  MALEFACTOR_ALIGNMENT,
  DESTROYER_ALIGNMENT
};
typedef enum character_sheet_alignments alignments;

struct character_sheet {
  string name;
  uint64_t experience;
  character_classes class;
  races race;
  alignments alignment;
  struct {
    uint32_t strength;
    uint32_t dexterity;
    uint32_t constitution;
    uint32_t intelligence;
    uint32_t wisdom;
    uint32_t charisma;
  } saving_throws;
  int32_t armor_class;
  int32_t current_hit_points;
  int32_t maximum_hit_points;
  uint32_t dying_throws[5];
  bool alive;
};
typedef struct character_sheet character_sheet;

// Convert an ability score in the range of 1 to 30 to a modifier in the range
// of -5 to 10
static inline int32_t
modifier_from_ability_score(const uint32_t ability_score) {
  return (int32_t)lround(.5 * ability_score - 5.2);
}

void set_saving_throws_for_new_character(character_sheet *character);
character_sheet create_random_playable_character(void);
