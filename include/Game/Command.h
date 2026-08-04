#pragma once

#include <variant>

#include "Miscellaneous/Coords.h"

/* === WORLD MAP === */
struct MoveCharacter {
  int character_id;
  CoordPair destination;
};

struct EndTurn {};

using WorldMapCommand = std::variant<MoveCharacter, EndTurn>;

/* === TOWN === */

/* === BATTLE === */

struct MoveStack {
  int stack_id;
  CoordPair destination;
};
struct AttackStack {
  int attacker_id;
  CoordPair attacked_tile;
};
struct Wait {
  int stack_id;
};
struct Defend {
  int stack_id;
};
using BattleCommand = std::variant<MoveStack, AttackStack, Wait, Defend>;

/* === GENERAL WRAPPER === */

using Command = std::variant<WorldMapCommand, BattleCommand>;
