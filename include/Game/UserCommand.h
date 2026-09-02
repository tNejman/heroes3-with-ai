#pragma once

#include <variant>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

/* === WORLD MAP === */
struct MoveCharacter {
  CoordPair source_;
  CoordPair destination_;
};

struct EndTurn {};

using WorldMapCommand = std::variant<MoveCharacter, EndTurn>;

/* === TOWN === */

using TownCommand = std::variant<std::monostate>;

/* === BATTLE === */

// struct MoveStack {
//   CoordPair destination;
// };
// struct AttackStack {
//   CoordPair destination;
// };
// struct Wait {};
// struct Defend {};

// using BattleCommand = std::variant<MoveStack, AttackStack, Wait, Defend>;

struct BattleCommand {
  enum class Action : char { MOVE, ATTACK, WAIT, DEFEND } action;

  CoordPair destination;
};

/* === GAME === */

struct SwitchCharacter {};

using StateIndependentCommand = std::variant<SwitchCharacter>;

/* === GENERAL WRAPPER === */

using None = std::monostate;

using UserCommand = std::variant<WorldMapCommand, TownCommand, BattleCommand, StateIndependentCommand, None>;
