#pragma once

#include <variant>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

/* === WORLD MAP === */
struct MoveCharacter {
  CharacterMoveDirection direction;
};

struct EndTurn {};

using WorldMapCommand = std::variant<MoveCharacter, EndTurn>;

/* === TOWN === */

using TownCommand = std::variant<std::monostate>;

/* === BATTLE === */

struct MoveStack {
  CoordPair destination;
};
struct AttackStack {
  CoordPair destination;
};
struct Wait {
  int stack_id;
};
struct Defend {
  int stack_id;
};
using BattleCommand = std::variant<MoveStack, AttackStack, Wait, Defend>;

/* === GENERAL WRAPPER === */

using None = std::monostate;

using UserCommand = std::variant<WorldMapCommand, TownCommand, BattleCommand, None>;