// SPDX-License-Identifier: GPL-2.0-only

#include <stdlib.h>

#include "krall/character_sheet.h"
#include "krall/comparison.h"
#include "krall/rng.h"

const string_view saving_throws_names_map[NUMBER_OF_SAVING_THROWS] = {
    {.number_of_bytes = sizeof("Strength"), .characters = "Strength"},
    {.number_of_bytes = sizeof("Dexterity"), .characters = "Dexterity"},
    {.number_of_bytes = sizeof("Constitution"), .characters = "Constitution"},
    {.number_of_bytes = sizeof("Intelligence"), .characters = "Intelligence"},
    {.number_of_bytes = sizeof("Wisdom"), .characters = "Wisdom"},
    {.number_of_bytes = sizeof("Charisma"), .characters = "Charisma"}};

const saving_throws
    rogue_class_saving_throws_priority_map[NUMBER_OF_SAVING_THROWS] = {
        WISDOM_THROW,   CONSTITUTION_THROW, STRENGTH_THROW,
        CHARISMA_THROW, INTELLIGENCE_THROW, DEXTERITY_THROW};

const saving_throws
    barbarian_class_saving_throws_priority_map[NUMBER_OF_SAVING_THROWS] = {
        INTELLIGENCE_THROW, WISDOM_THROW,       CHARISMA_THROW,
        DEXTERITY_THROW,    CONSTITUTION_THROW, STRENGTH_THROW};

const saving_throws
    ranger_class_saving_throws_priority_map[NUMBER_OF_SAVING_THROWS] = {
        CHARISMA_THROW, CONSTITUTION_THROW, INTELLIGENCE_THROW,
        STRENGTH_THROW, WISDOM_THROW,       DEXTERITY_THROW};

const saving_throws
    monk_class_saving_throws_priority_map[NUMBER_OF_SAVING_THROWS] = {
        INTELLIGENCE_THROW, CHARISMA_THROW, STRENGTH_THROW,
        CONSTITUTION_THROW, WISDOM_THROW,   DEXTERITY_THROW};

const saving_throws (
        *const saving_throws_priority_map_by_character_class
            [NUMBER_OF_CHARACTER_CLASSES])[NUMBER_OF_SAVING_THROWS] = {
    &rogue_class_saving_throws_priority_map,
    &barbarian_class_saving_throws_priority_map,
    &ranger_class_saving_throws_priority_map,
    &monk_class_saving_throws_priority_map};

const string_view character_classes_names_map[NUMBER_OF_CHARACTER_CLASSES] = {
    {.number_of_bytes = sizeof("Rogue"), .characters = "Rogue"},
    {.number_of_bytes = sizeof("Barbarian"), .characters = "Barbarian"},
    {.number_of_bytes = sizeof("Ranger"), .characters = "Ranger"},
    {.number_of_bytes = sizeof("Monk"), .characters = "Monk"}};

const string_view races_names_map[NUMBER_OF_RACES] = {
    {.number_of_bytes = sizeof("Dragonborn"), .characters = "Dragonborn"},
    {.number_of_bytes = sizeof("Drow"), .characters = "Drow"},
    {.number_of_bytes = sizeof("Dwarf"), .characters = "Dwarf"},
    {.number_of_bytes = sizeof("Elf"), .characters = "Elf"},
    {.number_of_bytes = sizeof("Gnome"), .characters = "Gnome"},
    {.number_of_bytes = sizeof("Half-Elf"), .characters = "Half-Elf"},
    {.number_of_bytes = sizeof("Halfling"), .characters = "Halfling"},
    {.number_of_bytes = sizeof("Half-Orc"), .characters = "Half-Orc"},
    {.number_of_bytes = sizeof("Human"), .characters = "Human"},
    {.number_of_bytes = sizeof("Tiefling"), .characters = "Tiefling"},
    {.number_of_bytes = sizeof("Orc"), .characters = "Orc"},
    {.number_of_bytes = sizeof("Leonin"), .characters = "Leonin"},
    {.number_of_bytes = sizeof("Satyr"), .characters = "Satyr"},
    {.number_of_bytes = sizeof("Owlin"), .characters = "Owlin"},
    {.number_of_bytes = sizeof("Svirfneblin"), .characters = "Svirfneblin"},
    {.number_of_bytes = sizeof("Duergar"), .characters = "Duergar"},
    {.number_of_bytes = sizeof("Firbolg"), .characters = "Firbolg"},
    {.number_of_bytes = sizeof("Goblin"), .characters = "Goblin"},
    {.number_of_bytes = sizeof("Goliath"), .characters = "Goliath"},
    {.number_of_bytes = sizeof("Kobold"), .characters = "Kobold"},
    {.number_of_bytes = sizeof("Tortle"), .characters = "Tortle"},
    {.number_of_bytes = sizeof("Yuan-ti"), .characters = "Yuan-ti"}};

static inline void distribute_saving_throw_rolls_prioritized_by_class(
    character_sheet *character, uint32_t rolls[NUMBER_OF_SAVING_THROWS]) {
  uint32_t *const character_throws[NUMBER_OF_SAVING_THROWS] = {
      &character->saving_throws.strength,
      &character->saving_throws.dexterity,
      &character->saving_throws.constitution,
      &character->saving_throws.intelligence,
      &character->saving_throws.wisdom,
      &character->saving_throws.charisma};

  const saving_throws(
          *const saving_throws_priority_map)[NUMBER_OF_SAVING_THROWS] =
      saving_throws_priority_map_by_character_class[character->class];

  for (size_t i = 0; i < NUMBER_OF_SAVING_THROWS; i++) {
    *(character_throws[*(*saving_throws_priority_map + i)]) = rolls[i];
  }
}

void set_saving_throws_for_new_character(character_sheet *character) {
  // Generate six saving throw rolls by,
  //  * rolling 24 1d6
  //  * sorting rolls from lowest to highest, disgarding the lowest four rolls
  //    and highest two rolls
  //  * splitting the rolls into six groups of three
  //  * summing the rolls in each group
  uint32_t unattributed_rolls[NUMBER_OF_SAVING_THROWS] = {0};

  {
    roll_some_dice(24, 6);

    qsort(some_dice_rolls, sizeof(some_dice_rolls) / sizeof(*some_dice_rolls),
          sizeof(*some_dice_rolls), uint32_t_comparison);

    for (size_t i = 0;
         i < sizeof(unattributed_rolls) / sizeof(*unattributed_rolls); i++) {
      unattributed_rolls[i] = some_dice_rolls[i * 3 + 4] +
                              some_dice_rolls[i * 3 + 5] +
                              some_dice_rolls[i * 3 + 6];
    }
  }

  // Distribute the highest rolls to the important saving throws per class.
  distribute_saving_throw_rolls_prioritized_by_class(character,
                                                     unattributed_rolls);
}

character_sheet create_random_playable_character(void) {
  character_sheet new_character = {0};

  new_character.class =
      (character_classes)(random_uint32_t() % NUMBER_OF_CHARACTER_CLASSES);

  new_character.race = (races)(random_uint32_t() % NUMBER_OF_RACES);

  set_saving_throws_for_new_character(&new_character);

  return new_character;
}

/*
printf(
    "x the %.*s %.*s [str %d, dex %d, con %d, int %d, wis %d, cha %d]\n",
    (int)races_names_map[random_character.race].number_of_bytes,
    races_names_map[random_character.race].characters,
    (int)character_classes_names_map[random_character.class].number_of_bytes,
    character_classes_names_map[random_character.class].characters,
    random_character.saving_throws.strength,
    random_character.saving_throws.dexterity,
    random_character.saving_throws.constitution,
    random_character.saving_throws.intelligence,
    random_character.saving_throws.wisdom,
    random_character.saving_throws.charisma);
*/
