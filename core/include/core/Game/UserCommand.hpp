#pragma once

#include <variant>

#include "aux/IsVariantMember.hpp"
#include "engine/IGame/Coords.h"

namespace game {

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

struct UserCommand {
  using V = std::variant<WorldMapCommand, TownCommand, BattleCommand, StateIndependentCommand, None>;
  V command_;

  template <typename T>
  requires IS_VARIANT_MEMBER_V<T, V>
  UserCommand( T opt ) : command_( opt ) {
  }
};

};  // namespace game